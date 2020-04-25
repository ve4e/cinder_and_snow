import QtQuick 2.14

Rectangle {
//    property string name: "Юнит"
//    property string img: "qrc:/units/img/unit_archer"
//    property int lvl: 0
//    property int health: 0
//    property int attack: 0
//    property int shooting: 0
//    property int shooting_distance: 0
//    property int movement: 0
    property variant unit

    property int margins: 9

    Text {
        id: node_1
        text: unit.name
        anchors.margins: margins
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
    }
    Image {
        id: node_2
        source: unit.img

        width: 80
        height: 80

        anchors.margins: margins
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: node_1.bottom
    }
    Text {
        id: node_3
        text: "Уровень: " + unit.lvl

        anchors.margins: margins
        anchors.left: parent.left
        anchors.top: node_2.bottom
    }
    Text {
        id: node_4
        text: "Здоровье: " + unit.health

        anchors.margins: margins
        anchors.left: parent.left
        anchors.top: node_3.bottom
    }

    Text {
        id: node_5
        text: "Атака: " + unit.attack

        anchors.margins: margins
        anchors.left: parent.left
        anchors.top: node_4.bottom
    }

    Text {
        id: node_6
        text: "Стрельба: " + unit.shooting

        anchors.margins: margins
        anchors.left: parent.left
        anchors.top: node_5.bottom
    }
    Text {
        id: node_7
        text: "Дальность стрельбы: " + unit.shootingDistance

        anchors.margins: margins
        anchors.left: parent.left
        anchors.top: node_6.bottom
    }
    Text {
        id: node_8
        text: "Предвижение: " + unit.movement

        anchors.margins: margins
        anchors.left: parent.left
        anchors.top: node_7.bottom
    }
}














