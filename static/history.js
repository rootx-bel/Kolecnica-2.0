// function draw(ids){
//     alert('fak')
// }
// var myMap, myCollection;

// ymaps.ready(function  () {

// 	myMap = new ymaps.Map('ymapid', {
//                     center: [56.3241,44.0014],
//                     zoom: 15,
// 					behaviors: ["scrollZoom","drag"]
//                 });	
				
// 	myCollection = new ymaps.GeoObjectCollection();			
				
// 	$.ajax({
// 	url:'/static/a.csv',
// 			success: function(data){
// 			var rows = data.split("\n");
// 			var src_res='';
// 			for(var i in rows){
// 			var colls=rows[i].split(";");//или другой символ разделитель
			
// 			// Устанавливаем координаты и содержимое балуна
// 			myPlacemark = new ymaps.Placemark([colls[5], colls[4]], {
//                     // Свойства 
// 					iden: colls[0],
// 					iconContent: colls[0],
//                     balloonContentHeader: '<div style="color:#ff0303;font-weight:bold">'+colls[1]+'</div>',
//                     balloonContentBody: '<div style="font-size:10px;"><strong>Адрес:</strong> '+colls[2]+'<br /><strong>Телефон:</strong> '+colls[3]+'</div>'              
//                 }, {
//                     // Опции
//                     preset: 'twirl#lightblueIcon'
//                 });

//              myCollection.add(myPlacemark);
			
// 			$('#menu').append('<li>'+colls[0]+'. '+'<a href="#" onClick="return go_point('+colls[0]+");"+'\">'+colls[1]+'</a></li>');
// 			}
// 			myMap.geoObjects.add(myCollection);
			
// 			myMap.setBounds(myCollection.getBounds());
// 			}
	
	
// 	});			

// });

// function go_point(id){
// myCollection.each(function (item) {
// if (item.properties.get('iden') == id) {
// var coord = item.geometry.getCoordinates();
// myMap.setCenter(coord, 16);
// item.balloon.open();
// }
// });	
// }



var myMap, myCollection, ids, params, result, counter;

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
    var rows = result.split(";");
	var src_res='';
    counter = 1;
	for(var i in rows){
	    var colls=rows[i].split("&");
		myPlacemark = new ymaps.Placemark([colls[0], colls[1]], {
                iden: counter,
                iconContent: counter,
                balloonContentHeader: '<div style="color:#ff0303;font-weight:bold">'+colls[0]+':'+colls[1]+'</div>',
                balloonContentBody: '<div style="font-size:10px;"><strong>Адрес:</strong> '+colls[0]+'<br /><strong>Телефон:</strong> '+colls[1]+'</div>'              
            }, {
                preset: 'twirl#lightblueIcon'
        });
        myCollection.add(myPlacemark);
        $('#menu').append('<li>'+counter+'. '+'<a href="#" onClick="return go_point('+counter+");"+'\">'+colls[0]+':'+colls[1]+'</a></li>');
        counter++;
    }
    myMap.geoObjects.add(myCollection);
    myMap.setBounds(myCollection.getBounds());

    // $.ajax({
	//     url:'/static/a.csv',
	// 	success: function(data){
	// 	var rows = data.split("\n");
	// 	var src_res='';
	// 	for(var i in rows){
	// 	var colls=rows[i].split(";");
	// 	myPlacemark = new ymaps.Placemark([colls[5], colls[4]], {
	// 				iden: colls[0],
	// 				iconContent: colls[0],
    //                 balloonContentHeader: '<div style="color:#ff0303;font-weight:bold">'+colls[1]+'</div>',
    //                 balloonContentBody: '<div style="font-size:10px;"><strong>Адрес:</strong> '+colls[2]+'<br /><strong>Телефон:</strong> '+colls[3]+'</div>'              
    //             }, {
    //                 // Опции
    //                 preset: 'twirl#lightblueIcon'
    //             });

    //          myCollection.add(myPlacemark);
			
	// 		$('#menu').append('<li>'+colls[0]+'. '+'<a href="#" onClick="return go_point('+colls[0]+");"+'\">'+colls[1]+'</a></li>');
	// 		}
	// 		myMap.geoObjects.add(myCollection);
			
	// 		myMap.setBounds(myCollection.getBounds());
	// 		}
	// });
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