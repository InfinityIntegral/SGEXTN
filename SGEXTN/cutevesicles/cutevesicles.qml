import QtQuick 6.9
import Resizer 0.0
import CuteVesicles 0.0

CuteVesicles{
    layer.enabled: true
    x: 0.5 * (Resizer.appWindowWidth - Resizer.renderSpaceWidth)
    y: 0.5 * (Resizer.appWindowHeight - Resizer.renderSpaceHeight) + Resizer.sizeUnit
    width: Resizer.renderSpaceWidth
    height: Resizer.renderSpaceHeight - Resizer.sizeUnit
}
