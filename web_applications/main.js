const params = new URLSearchParams(window.location.search);
const phrase = params.get("phrase");
const element = params.get("element");
const pics = [
	"air1.png",
	"air2.png",
	"air3.png",
	"earth1.png",
	"earth2.png",
	"earth3.png",
	"fire1.png",
	"fire2.png",
	"fire3.png",
	"water1.png",
	"water2.png",
	"water3.png",
	"yinyang.png",
].filter(s => s.startsWith(element));

var p_phrase = document.createElement("p");
var p_element = document.createElement("p");
var img = document.createElement("img");

p_phrase.innerHTML = "Phrase: " + phrase;
p_element.innerHTML = "Element: " + element;
img.src = "res/" + pics[Math.floor(Math.random() * pics.length)];
img.style = "width: 50%; border: 8px solid black;";

document.getElementById("topright").style.transform =
    "rotate(" + (phrase.length * 10) % 360 + "deg)";

document.body.appendChild(p_phrase);
document.body.appendChild(p_element);
document.body.appendChild(img);

switch (element) {
case "water":
	document.body.style.background = "lightblue";
	break;
case "earth":
	document.body.style.background = "darkolivegreen";
	break;
case "fire":
	document.body.style.background = "firebrick";
	break;
case "air":
	document.body.style.background = "lightyellow";
	break;
}
