import QtQuick
import ThemeColours 0.0
import Resizer 0.0

Rectangle{
	property int widgetType: 0
    property int bg: 6
    x: 0
    y: 0
    width: Resizer.appWindowWidth
    height: Resizer.appWindowHeight
    color: ThemeColours.getThemeColour(bg)
}
