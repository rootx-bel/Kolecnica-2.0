let myMap, myCollection, ids, params, result, counter, res, idm, counterl, flag;
flag = false;
function httpGet(theUrl, params)
{
    var xmlHttp = new XMLHttpRequest();
    xmlHttp.open( "GET", theUrl+"?ids="+params, false );
    xmlHttp.send( null );
    return xmlHttp.responseText;
}

ymaps.ready(function  () {
	myMap = new ymaps.Map('ymapid', {
                    center: [50.5907, 36.5802],
                    zoom: 13,
					behaviors: ["scrollZoom","drag"]
                })
    myCollection = new ymaps.GeoObjectCollection();	
});

function draw(ids){
    result = httpGet('http://127.0.0.1/geo', ids);
    $('#menu').empty();
    $('#menul').empty();
    if(flag){
        myCollection.removeAll();
        myMap.geoObjects.add(myCollection);
    }
    flag = true;
    let koordspl = result.split("*");
    var rows = koordspl[0].split(";");
	var src_res='';
    counter = 1;
	for(var i in rows){
	    var colls=rows[i].split("&");
		myPlacemark = new ymaps.Placemark([colls[0], colls[1]], {
                iden: counter,
                iconContent: counter,
                balloonContentHeader: '<div style="color:#ff0303;font-weight:bold">'+colls[0]+':'+colls[1]+'</div>',
                balloonContentBody: '<div style="font-size:10px;"><strong>Температура:</strong> '+colls[2]+'</div>'              
            }, {
                preset: 'twirl#lightblueIcon'
        });
        myCollection.add(myPlacemark);
        $('#menu').append('<li>'+counter+'. '+'<a href="#" onClick="return go_point('+counter+");"+'\">'+colls[0]+':'+colls[1]+'</a></li>');
        counter++;
    }

    var rowsl = koordspl[1].split(";");
	var src_resl='';
    counterl = 11;
	for(var i in rowsl){
	    var collsl=rowsl[i].split("&");
		myPlacemark = new ymaps.Placemark([collsl[0], collsl[1]], {
                iden: counterl,
                iconContent: counterl,
                balloonContentHeader: '<div style="color:#ff0303;font-weight:bold">'+collsl[0]+':'+collsl[1]+'</div>'            
            }, {
                preset: 'twirl#lightredIcon'
        });
        myCollection.add(myPlacemark);
        $('#menul').append('<li>'+counterl+'. '+'<a href="#" onClick="return go_point('+counterl+");"+'\">'+collsl[0]+':'+collsl[1]+'</a></li>');
        counterl+=10;
    }

    myMap.geoObjects.add(myCollection);
    myMap.setBounds(myCollection.getBounds());
}

function go_point(id){
    myCollection.each(function (item) {
    if (item.properties.get('iden') == id) {
        var coord = item.geometry.getCoordinates();
        myMap.setCenter(coord, 16);
        item.balloon.open();
    }
    });	
}