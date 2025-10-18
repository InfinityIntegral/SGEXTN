import QtQuick
import ThemeColours 0.0
import Resizer 0.0

Rectangle{
	x: 0
	y: Resizer.sizeUnit
    width: Resizer.renderSpaceWidth
    height: Resizer.renderSpaceHeight - Resizer.sizeUnit
    color: ThemeColours.getThemeColour(8)
}
