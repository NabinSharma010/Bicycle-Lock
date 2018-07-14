const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE HTML>
<html>
  <head>
    <title>BICYCLE LOCK</title>
    <meta name= "viewport " content= "width=device-width, initial-scale=1.0 ">

    <script>
    
    function getRandomInt(max) 
    {
      return Math.floor(Math.random() * Math.floor(max));
     }
     
 
    function s(u){var x = new XMLHttpRequest();x.open("GET", u+"?x="+getRandomInt(10000), true);x.send(null);}
    function ret(u){return function(e){
                                s(u);
                                e.returnValue = false;
                                return false;
                            }

                     }

       window.addEventListener('load', function(){
         var Unlock = document.getElementById('Unlock');
         var Lock = document.getElementById('Lock');
         Unlock.addEventListener('touchstart', ret("Unlock"), false); 
         Lock.addEventListener('touchstart', ret("Lock"),false);
       }, false);


    </script>
  </head>
  
<body style= "height:100%;margin:0;background:#f6f6f6; ">
<div style= "height:6%;text-align:center;padding:3px;background:#4caf50;color:white; ">
<h3>HELLO WORLD</h3>
</div>
<br/>
<div style= "color:#f57c00;text-align:center;font-size:20px;font-weight:bold; ">UNLOCK BICYCLE</div>
<div style= "color:#f57c00;text-align:center;font-size:20px;font-weight:bold; ">LOCK BICYCLE</div>

<div style= "color:#212121;text-align:center; ">Status</div>
<br/>
<br/>
<div style= "text-align:center; ">
<center>
<button id = "Unlock" style= "color:white;background:#607d8b;padding:10px;border-radius:10px;text-decoration: none; ">UNLOCK BICYCLE</button>
</center>
</div>
<br/>
<br/>"
<div style= "text-align:center; ">
<center>
<button id = "Lock" style= "color:white;background:#607d8b;padding:10px;border-radius:10px;text-decoration: none; ">LOCK BICYCLE </button>
</center>
</div>
</body>
</html>
)=====";
