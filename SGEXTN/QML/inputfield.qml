import QtQuick
import QtQuick.Controls
import ThemeColours 0.0
import Resizer 0.0
import SingCorrect 0.0

TextField{
	property bool isInputField: true
	property int widgetType: 0
	property string fontClass: "SingScript.sg"
	property int bg: 4
	property int fg: 8
	property int bgHover: 3
	property int fgHover: 7
	property int bgFocus: 2
	property int fgFocus: 6
	property int bgSelected: 6
	property int fgSelected: 2
	property int bgInvalid: 6
	property int fgInvalid: 8
	property real x1: 0.0
	property real x0: 0.0
	property real y1: 0.0
	property real y0: 0.0
	property real w1: 0.0
	property real w0: 0.0
	property real h1: 0.0
	property real h0: 0.0
	property bool invalid: false
	
	x: x1 * Resizer.renderSpaceWidth + x0 * Resizer.sizeUnit
	y: y1 * Resizer.renderSpaceHeight + y0 * Resizer.sizeUnit
	width: w1 * Resizer.renderSpaceWidth + w0 * Resizer.sizeUnit
    height: h1 * Resizer.renderSpaceHeight + h0 * Resizer.sizeUnit
	property int bgNow: bg
	property int fgNow: fg
	padding: 0
	
	function emitClickedSignal(){
		text = SingCorrect.correct(text);
		if(noSendSignal == false && objectName == "0"){objectName = "1";}
		else if(noSendSignal == false){objectName = "0";}
	}
	objectName: "0"
	property bool noSendSignal: false
	onTextChanged: emitClickedSignal()
	
	function updateInteraction(){
		if(invalid){
			bgNow = bgInvalid;
			fgNow = fgInvalid;
		}
		else if(activeFocus){
			bgNow = bgFocus;
			fgNow = fgFocus;
		}
		else if(hovered){
			bgNow = bgHover;
			fgNow = fgHover;
		}
		else{
			bgNow = bg;
			fgNow = fg;
		}
	}
	
	property string timerSourceCode: `
	import QtQuick
	
	Timer{
		interval: 1000
		repeat: false
		running: true
		onTriggered: {parent.invalid = false; destroy();}
	}
	`
	
	function resetInvalid(){
		if(invalid){
			Qt.createQmlObject(timerSourceCode, this);
		}
	}
	
	onActiveFocusChanged: updateInteraction();
	onHoveredChanged: updateInteraction();
	onInvalidChanged: {updateInteraction(); resetInvalid();}
	
	background: Rectangle{
		x: 0
		y: 0
		width: parent.width
		height: parent.height
		color: ThemeColours.getThemeColour(bgNow)
	}
	
	font.pixelSize: height
	font.family: fontClass
	horizontalAlignment: Text.AlignHCenter
	color: ThemeColours.getThemeColour(fgNow)
	selectionColor: ThemeColours.getThemeColour(bgSelected);
	selectedTextColor: ThemeColours.getThemeColour(fgSelected);
}
