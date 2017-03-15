metadata {
    definition (name: "Xbee switch test", namespace: "tjsimmons.test", author: "T.J. Simmons") {
        capability "Switch"

        fingerprint inClusters: "0000,0003,0006", endpointId: "08", profileId: "0104"
    }

    command "on"
    command "off"

    simulator {
        status "on":"on/off: 1"
        status "off":"on/off: 0"

        reply "zcl on-off on":"on/off: 1"
        reply "zcl on-off off":"on/off: 0"
    }

    tiles {
        standardTile("switch", "device.switch", width: 2, height: 2, canChangeIcon: true) {
            state "off", label: "Off", action: "switch.on", icon: "st.doors.garage.garage-closed", backgroundColor: "#ffffff"
            state "on", label: "On", action: "switch.off", icon: "st.doors.garage.garage-open", backgroundColor: "st.colors.red"
        }

        main "switch"
        details(["switch"])
    }
}

def parse(String description) {
    log.info description

    if (description?.startsWith("catchall:")) {
        def value = name == "switch" ? (description?.endsWith(" 1") ? "on" : "off") : null
        def result = createEvent(name: name, value: value)
        def msg = zigbee.parse(description)

        log.debug "Parse returned ${result?.descriptionText}"

        return result

        log.trace msg
        log.trace "data: $msg.data"
    } else {
        def name = description?.startsWith("on/off: ") ? "switch" : null
        def value = name == "switch" ? (description?.endsWith(" 1") ? "on" : "off") : null
        log.debug "Parse returned ${result?.descriptionText}"

        return result
    }
}

def on() {
    log.debug "Executing on()"
    sendEvent(name: "switch", value: "on")
    "st cmd 0x${device.deviceNetworkId} ${endpointId} 6 1 {}"
    'zcl on-off on'
}

def off() {
    log.debug "Executing off()"
    sendEvent(name: "switch", value: "off")
    "st cmd 0x${device.deviceNetworkId} ${endpointId} 6 0 {}"
    'zcl on-off off'
}
