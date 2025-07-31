import QtQuick
import ThemeColours 0.0
import Resizer 0.0

Rectangle{
	property int widgetType: 0
	property int bg: -1
	property real x1: 0.0
	property real x0: 0.0
	property real y1: 0.0
	property real y0: 0.0
	property real w1: 0.0
	property real w0: 0.0
	property real h1: 0.0
	property real h0: 0.0
	property bool frequentlyUsed: false
	
	x: x1 * Resizer.renderSpaceWidth + x0 * Resizer.sizeUnit
	y: y1 * Resizer.renderSpaceHeight + y0 * Resizer.sizeUnit
    width: w1 * Resizer.renderSpaceWidth + w0 * Resizer.sizeUnit
    height: h1 * Resizer.renderSpaceHeight + h0 * Resizer.sizeUnit
    color: ThemeColours.getThemeColour(bg)
	
	MultiPointTouchArea{
		x: 0
		y: 0
		width: parent.width
		height: parent.height
	}
	MouseArea{
		x: 0
		y: 0
		width: parent.width
		height: parent.height
		hoverEnabled: true
	}
}
