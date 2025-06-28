import QtQuick 6.9
import QtQuick.Controls 6.9
import ThemeColours 0.0
import Resizer 0.0

ScrollView{
	property int widgetType: 0
	property int bg: -1
	property int bgScrollbar: 4
	property int fgScrollbar: 6
	property int bgScrollbarHover: 3
	property int fgScrollbarHover: 5
	property int bgScrollbarPress: 2
	property int fgScrollbarPress: 4
	property real x1: 0.0
	property real x0: 0.0
	property real y1: 0.0
	property real y0: 0.0
	property real w1: 0.0
	property real w0: 0.0
	property real h1: 0.0
	property real h0: 0.0
	property real ih1: 0.0
	property real ih0: 0.0
	property real s1: 0.0
	property real s0: 0.0
	property string s: ""
	
	x: x1 * Resizer.renderSpaceWidth + x0 * Resizer.sizeUnit
	y: y1 * Resizer.renderSpaceHeight + y0 * Resizer.sizeUnit
	width: w1 * Resizer.renderSpaceWidth + w0 * Resizer.sizeUnit
	height: h1 * Resizer.renderSpaceHeight + h0 * Resizer.sizeUnit
	
	ScrollBar.horizontal.policy: ScrollBar.AlwaysOff
	contentWidth: width
	clip: true
	
	Column{
		width: parent.width
		
		Rectangle{
			property bool canParent: true
			width: parent.width
			height: Math.max(h1 * Resizer.renderSpaceHeight + h0 * Resizer.sizeUnit, ih1 * Resizer.renderSpaceHeight + ih0 * Resizer.sizeUnit)
			color: ThemeColours.getThemeColour(bg);
		}
	}
	
	ScrollBar.vertical: ScrollBar{
		property int bgNow: bgScrollbar
		property int fgNow: fgScrollbar
		
		function updateInteraction(){
			if(pressed){
				bgNow = parent.bgScrollbarPress;
				fgNow = parent.fgScrollbarPress;
			}
			else if(hovered){
				bgNow = parent.bgScrollbarHover;
				fgNow = parent.fgScrollbarHover;
			}
			else{
				bgNow = parent.bgScrollbar;
				fgNow = parent.fgScrollbar;
			}
		}
		
		onPressedChanged: updateInteraction()
		onHoveredChanged: updateInteraction()
		policy: ScrollBar.AlwaysOn
		
		x: parent.width - width
		y: 0
		width: s1 * Resizer.renderSpaceWidth + s0 * Resizer.sizeUnit
		height: parent.height
		padding: 0
		
		contentItem: Rectangle{
			color: ThemeColours.getThemeColour(parent.fgNow)
			width: parent.width
		}
		background: Rectangle{
			color: ThemeColours.getThemeColour(parent.bgNow)
			width: parent.width
		}
	}
}
