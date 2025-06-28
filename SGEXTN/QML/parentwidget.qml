import QtQuick 6.9
import ThemeColours 0.0
import Resizer 0.0

Rectangle{
	property int widgetType: 0
	property int bg: 8
	x: 0.5 * (Resizer.appWindowWidth - Resizer.renderSpaceWidth)
	y: 0.5 * (Resizer.appWindowHeight - Resizer.renderSpaceHeight) + Resizer.sizeUnit
    width: Resizer.renderSpaceWidth
    height: Resizer.renderSpaceHeight - Resizer.sizeUnit
    color: ThemeColours.getThemeColour(bg)
}
