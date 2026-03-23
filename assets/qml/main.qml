import QtQuick 6.5
import QtQuick.Controls 6.5
import QtQuick.Layouts 6.5

ApplicationWindow {
    id: window
    width: 1200
    height: 800
    visible: true
    title: "AutoQuick"
    
    color: "#f4f7f8"

    property color colorPrimary: "#7fb7be"
    property color colorSecondary: "#d3f3ee"
    property color colorBg: "#ffffff"
    property color colorAppBg: "#f4f7f8"
    property color colorTextMain: "#2c3e50"
    property color colorTextMuted: "#7f8c8d"
    property color colorBorder: "#e0e6ed"
    property color colorHover: "#f0f4f8"

    MouseArea {
        anchors.fill: parent
        enabled: toolBar.openMenuName !== "" 
        hoverEnabled: true 
        onClicked: toolBar.openMenuName = ""
    }

    header: ToolBar {
        id: toolBar

        property string openMenuName: ""

        property var menuStructure: [
            { title: "Timetable", items: ["View Timetable", "New Timetable", "Export..."] },
            { title: "Edit",      items: ["Undo", "Redo", "Cut", "Copy", "Paste"] },
            { title: "Search",    items: ["Find", "Replace", "Find in Files"] },
            { title: "View",      items: ["Appearance", "Zoom In", "Zoom Out"] },
            { title: "Tools",     items: ["Run Script", "Debugger"] },
            { title: "Configure", items: ["Settings", "Keyboard Shortcuts"] },
            { title: "Help",      items: ["Documentation", "About AutoQuick"] }
        ]

        Rectangle {
            id: customToolBar
            width: parent.width
            height: 35
            color: window.colorBg
            z: 2

            Rectangle {
                width: parent.width
                height: 1
                color: window.colorBorder
                anchors.bottom: parent.bottom
            }

            RowLayout {
                anchors.fill: parent
                spacing: 2

                Label {
                    text: "AutoQuick"
                    font.pixelSize: 13
                    font.bold: true
                    color: window.colorTextMain
                    Layout.leftMargin: 15
                    Layout.rightMargin: 15
                    Layout.alignment: Qt.AlignVCenter
                }

                Repeater {
                    model: toolBar.menuStructure

                    delegate: Item {
                        id: menuContainer
                        Layout.preferredWidth: topButtonText.implicitWidth + 20
                        Layout.fillHeight: true

                        property bool isOpen: toolBar.openMenuName === modelData.title

                        Rectangle {
                            anchors.fill: parent
                            anchors.margins: 3
                            radius: 4
                            color: menuContainer.isOpen ? colorBorder : (topMouseArea.containsMouse ? colorHover : "transparent")

                            Text {
                                id: topButtonText
                                anchors.centerIn: parent
                                text: modelData.title
                                font.pixelSize: 13
                                color: colorTextMain
                            }

                            MouseArea {
                                id: topMouseArea
                                anchors.fill: parent
                                hoverEnabled: true
                                onClicked: {
                                    if (toolBar.openMenuName === modelData.title) {
                                        toolBar.openMenuName = ""
                                    } else {
                                        toolBar.openMenuName = modelData.title
                                    }
                                }
                            }
                        }

                        Rectangle {
                            id: dropdownBox
                            visible: menuContainer.isOpen
                            y: menuContainer.height 
                            x: 0
                            width: Math.max(160, dropdownCol.implicitWidth + 10) 
                            height: dropdownCol.implicitHeight + 10
                            color: colorBg
                            border.color: colorBorder
                            border.width: 1
                            radius: 5
                            z: 10 

                            Column {
                                id: dropdownCol
                                anchors.fill: parent
                                anchors.margins: 5
                                spacing: 1

                                Repeater {
                                    model: modelData.items

                                    delegate: Rectangle {
                                        width: dropdownBox.width - 10
                                        height: 28
                                        radius: 4
                                        color: itemMouseArea.containsMouse ? colorPrimary : "transparent"

                                        Text {
                                            anchors.verticalCenter: parent.verticalCenter
                                            anchors.left: parent.left
                                            anchors.leftMargin: 10
                                            text: modelData
                                            font.pixelSize: 12
                                            color: itemMouseArea.containsMouse ? colorBg : colorTextMain 
                                        }

                                        MouseArea {
                                            id: itemMouseArea
                                            anchors.fill: parent
                                            hoverEnabled: true
                                            onClicked: {
                                                console.log("Triggered Action: " + modelData)
                                                toolBar.openMenuName = "" 
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }

                Item { Layout.fillWidth: true } 
            }
        }
    }

    RowLayout {
        anchors.fill: parent
        spacing: 0
        
        ColumnLayout {
            Layout.fillWidth: true
            Layout.fillHeight: true
            spacing: 0
            
            ListView {
                id: timetableList
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.margins: 32
                clip: true
                spacing: 16
                
                model: ListModel {
                    ListElement { day: "Mon"; className: "Math"; path: "C:\\path\\to\\math\\notes" }
                    ListElement { day: "Tue"; className: "Physics"; path: "C:\\path\\to\\physics\\lab" }
                }

                delegate: Rectangle {
                    width: ListView.view.width
                    height: 80
                    radius: 12
                    color: "#ffffff"
                    border.color: "#e0e6ed"
                    border.width: 1
                    
                    RowLayout {
                        anchors.fill: parent
                        anchors.leftMargin: 24
                        anchors.rightMargin: 24
                        spacing: 24

                        Rectangle {
                            Layout.preferredWidth: 60
                            Layout.preferredHeight: 48
                            radius: 8
                            color: "#d3f3ee"
                            
                            Label {
                                anchors.centerIn: parent
                                text: model.day
                                font.pixelSize: 16
                                font.weight: Font.Bold
                                color: "#7fb7be"
                            }
                        }
                        
                        Label {
                            text: model.className
                            font.pixelSize: 18
                            font.weight: Font.DemiBold
                            color: "#2c3e50"
                            Layout.preferredWidth: 150
                        }
                        
                        Label {
                            text: model.path
                            font.pixelSize: 14
                            color: "#7f8c8d"
                            elide: Text.ElideRight
                            Layout.fillWidth: true
                        }
                        
                        Button {
                            text: "Remove"
                            Layout.preferredWidth: 100
                            Layout.preferredHeight: 36
                            contentItem: Text {
                                text: parent.text
                                color: parent.down ? "#ffffff" : "#7fb7be"
                                horizontalAlignment: Text.AlignHCenter
                                verticalAlignment: Text.AlignVCenter
                                font.weight: Font.Medium
                            }
                            background: Rectangle {
                                radius: 6
                                color: parent.down ? "#7fb7be" : "transparent"
                                border.color: "#7fb7be"
                                border.width: 1.5
                            }
                            onClicked: console.log("Remove " + model.className)
                        }
                    }
                }
            }

            Rectangle {
                Layout.fillWidth: true
                Layout.preferredHeight: 100
                color: "#ffffff"
                border.color: "#e0e6ed"
                border.width: 1
                
                RowLayout {
                    anchors.fill: parent
                    anchors.margins: 20
                    spacing: 20
                    
                    Rectangle {
                        Layout.preferredWidth: 60
                        Layout.preferredHeight: 60
                        radius: 12
                        color: "#f4f7f8"
                        border.color: "#e0e6ed"
                        border.width: 1
                        Label {
                            anchors.centerIn: parent
                            text: "⚙" 
                            font.pixelSize: 24
                            color: "#7f8c8d"
                        }
                    }

                    Rectangle {
                        Layout.preferredWidth: 80
                        Layout.preferredHeight: 60
                        radius: 12
                        color: "#f4f7f8"
                        border.color: "#e0e6ed"
                        border.width: 1
                        Label {
                            anchors.centerIn: parent
                            text: "⇄"
                            font.pixelSize: 24
                            color: "#7f8c8d"
                        }
                    }

                    Rectangle {
                        Layout.fillWidth: true
                        Layout.preferredHeight: 60
                        radius: 12
                        color: "#f4f7f8"
                        border.color: colorBorder
                        border.width: 1
                        
                        Label {
                            anchors.centerIn: parent
                            text: "Dashboard Overview"
                            color: "#7f8c8d"
                            font.pixelSize: 14
                        }
                    }

                    Button {
                        text: "+ Add Item"
                        Layout.preferredWidth: 140
                        Layout.preferredHeight: 50
                        Layout.alignment: Qt.AlignVCenter
                        contentItem: Text {
                            text: parent.text
                            color: "#ffffff"
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                            font.weight: Font.Bold
                            font.pixelSize: 15
                        }
                        background: Rectangle {
                            radius: 8
                            color: "#7fb7be"
                        }
                        onClicked: console.log("add clicked")
                    }
                }
            }
        }
    }
}