// Tab Name | URL | * (Default Selected Tab)
var tabs = new Array
(
	"MSDN|http://msdn.microsoft.com",
	"CNN|http://www.cnn.com",
	"NASA|http://www.nasa.gov",
	"Google|http://www.google.com|*",
	"Forbes|http://www.forbes.com"
);

// Align Tab: LEFT, CENTER, RIGHT
var tabAlign = "RIGHT";

/*********************************************/

function tabOnClick(ID)
{
	var oElement = null;

	for (var i = 0; i < tabs.length; i++)
	{
		oElement = document.getElementById(i);
		oElement.className = "tabOff";
	}

	oElement = document.getElementById(ID);
	oElement.className = "tabOn";

	var tab = tabs[ID].split("|");
	divTabFrame.innerHTML = "<IFRAME SRC="+tab[1]+" CLASS='tabFrame'></IFRAME>";

	document.body.focus();
}

function tabLoad()
{
	var HTML = "";

	HTML += "<P ALIGN="+tabAlign+">";
	for (var i = 0; i < tabs.length; i++)
	{
		var tab = tabs[i].split("|");
		HTML += "<INPUT TYPE='BUTTON' ID="+i+" CLASS='tabOff' VALUE="+tab[0]+" onClick='tabOnClick("+i+")'>&nbsp;";
	}

	divTabButtons.innerHTML = HTML;

	for (var i = 0; i < tabs.length; i++)
	{
		var tab = tabs[i].split("|");

		if (tab[2] == "*")
		{
			tabOnClick(i);
			
			break;			
		}
	}
}