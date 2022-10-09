<html xmlns="http://www.w3.org/1999/xhtml">
<head>
    <title>Добавление меток пользователями</title>
    <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
    <script src="http://api-maps.yandex.ru/1.1/index.xml?key=ACuF2EkBAAAAzahYCgIASLsFm9n8EPvNjaTc8nAWiETKgYcAAAAAAAAAAAC-q61vWtIK3Kzt2yQ9qFaGJGKzXw==" type="text/javascript"></script>

<script type="text/javascript" charset="utf-8">
		 var map;
		 function init () {
		   map = new YMaps.Map( document.getElementById("YMapsID") );
		   map.setCenter(new YMaps.GeoPoint(43.979459,56.291908), 15, 
				  YMaps.MapType.MAP);

YMaps.Events.observe(map, map.Events.Click, function (map, mEvent) {
                var myHtml = "Значение: " + mEvent.getGeoPoint() + "<br>"+'<form id="formadd" name="formadd_point" method="post" action=""><p>Название: <input name="namepoint" type="text" size="20" maxlength="80" /></p><p>Описание: <textarea name="descriptpoint" cols="20" rows="5"></textarea></p><input name="pcoord" type="hidden" value="'+mEvent.getGeoPoint()+'" /><p><input name="subpoint" type="submit" value="Добавить" /></p></form>';
                map.openBalloon(mEvent.getGeoPoint(), myHtml);
            });

      
            map.addControl(new YMaps.TypeControl());
            map.addControl(new YMaps.ToolBar());
            map.addControl(new YMaps.Zoom());

}
 
		</script>
	</head>

	<body onload="init();">
		<div id="YMapsID" style="width:600px; height:400px;"></div>

<p><a href="http://webmap-blog.ru/?p=220" title="Яндекс.Карта на Вашем сайте с возможностью добавления меток пользователями" target="_blank">Вернуться к тексту заметки</a></p> 
</body>
</html> 