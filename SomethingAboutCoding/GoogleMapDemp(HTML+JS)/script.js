function myMap() {
    /*--------------------Map initialization---------------------------*/
    // mapProp is setting up properties
    var mapProp= {
      center:new google.maps.LatLng(35.00000,139.00000),    // define zoom center in initilization
      zoom:6,                                               // define zoom level (far 0 ~ 8 near)
    };
    // get element by name
    var mapCanvas = document.getElementById("googleMap");
    // call Google Map API, with elements and mapProp properties
    var map=new google.maps.Map(mapCanvas, mapProp);

    /*----------------------Put balloons on Oil bases------------------------*/
    var base1 = new google.maps.LatLng(35.457241, 139.697550);
    var marker_base1 = new google.maps.Marker({
        position: base1,
        //animation: google.maps.Animation.BOUNCE,          // this animation keeps bouncing...
    });
    marker_base1.setMap(map);

    /*----------------------Prepare info window on a balloon------------------------*/
    // for base1's info window content
    var info_base1 = "<img src='img/MrBeans.gif'><br/><b>Base1</b><br/>123 Address<br/> City,Country";
    var infoWindow_base1 = new google.maps.InfoWindow({
        content: info_base1,
    });

    /*--------------Event listener, display info window when a balloon is clicked---------*/
    google.maps.event.addListener(marker_base1, 'click', function(){
        infoWindow_base1.open(map, marker_base1);
    });

}

const polygonURL = 'https://nominatim.openstreetmap.org/search.php?q=Japan&polygon_geojson=1&format=json'
function httpGetAsync(theUrl, callback)
{
    var xmlHttp = new XMLHttpRequest();
    xmlHttp.onreadystatechange = function() { 
        if (xmlHttp.readyState == 4 && xmlHttp.status == 200)
            callback(xmlHttp.responseText);
    }
    xmlHttp.open("GET", theUrl, true); // true for asynchronous 
    xmlHttp.send(null);
}
var JapanPolygon = httpGetAsync(polygonURL)