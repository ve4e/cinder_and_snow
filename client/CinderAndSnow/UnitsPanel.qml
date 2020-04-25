import QtQuick 2.14
import QtGraphicalEffects 1.0
import QtQuick.Controls 2.14



Item{
    signal unitClicked(unitId: int)
    id: root

//    ListModel{
//        id: unitModel
//    }

    GridView {

        cellWidth: 72; cellHeight: 72
        anchors.fill: parent
        model: unitModel
        delegate: unitDelegate

        Component {
            id: unitDelegate


            Item {
                id: unitItem

                Button{


                    id: unitButton

                    width: 70
                    height: 70

                    onClicked: {
                        root.unitClicked(ind)
                    }

                    contentItem:
                        Image {
                            id: unitImage
                            source: img
                        }
                }

                Text {
                    x: 5
                    font.pointSize: 16
                    font.bold: true
                    color: "#ffa940"
                    text: lvl
                }
            }
        }
    }
}
