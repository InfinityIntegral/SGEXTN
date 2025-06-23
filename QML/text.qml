import QtQuick 6.9
import ThemeColours 0.0
import Resizer 0.0

Rectangle{
	property int bg: 8
	property int fg: 4
	property real x1: 0.0
	property real x0: 0.0
	property real y1: 0.0
	property real y0: 0.0
	property real w1: 0.0
	property real w0: 0.0
	property real h1: 0.0
	property real h0: 0.0
	property string s: ""
	x: x1 * Resizer.renderSpaceWidth + x0 * Resizer.sizeUnit
	y: y1 * Resizer.renderSpaceHeight + y0 * Resizer.sizeUnit
    width: w1 * Resizer.renderSpaceWidth + w0 * Resizer.sizeUnit
    height: h1 * Resizer.renderSpaceHeight + h0 * Resizer.sizeUnit
    color: ThemeColours.getThemeColour(bg)
	Text{
		x: 0
		y: 0
		width: parent.width
		height: parent.height
		text: s
		font.pixelSize: parent.height
		font.family: "SingScript.sg"
		color: ThemeColours.getThemeColour(fg)
		clip: true
		elide: Text.ElideRight
	}
}
