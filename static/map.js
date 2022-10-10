let mymap, counter, hist;

hist = [];
counter = 0;
ymaps.ready(init);

function init(){
    myMap = new ymaps.Map('ymapid', {
        center: [50.5907, 36.5802],
        zoom: 13,
        behaviors: ["scrollZoom","drag"],
        controls: ['smallMapDefaultSet']
    });

    myCollection = new ymaps.GeoObjectCollection();

    myMap.events.add('click', function (e) {
            var coords = e.get('coords');
            hist[counter] = [coords[0].toPrecision(6), coords[1].toPrecision(6)];
            // alert(coords[0].toPrecision(6)+" "+coords[1].toPrecision(6));
            myPlacemark = new ymaps.Placemark(coords, {
                iden: counter+1,
                iconContent: counter+1,            
            }, {
                preset: 'islands#greenIcon',
                draggable: true
            });
            myCollection.add(myPlacemark);
            myMap.geoObjects.add(myCollection);
            counter++;
        });
}
function httpGet(theUrl, params)
{
    var xmlHttp = new XMLHttpRequest();
    xmlHttp.open( "GET", theUrl+"?keys="+params, false );
    xmlHttp.send( null );
    return xmlHttp.responseText;
}
function clea() {
    counter = 0;
    myCollection.removeAll();
    myMap.geoObjects.add(myCollection);
    hist = [];
}
// function traek() {}
function bound() {
    myMap.setBounds(myCollection.getBounds());
}
function sendm() {
    // console.log(hist);
    httpGet('http://127.0.0.1/comm', hist);
}