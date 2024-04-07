STRINGIFY(
(() => {
    let proto_events = ["bubbles", "cancelable", "composed", "currentTarget", "defaultPrevented",
        "eventPhase", "isTrusted", "target", "timeStamp", "type"];
    let proto_subevent = {
        "AnimationEvent": ["animationName", "elapsedTime", "pseudoElement"],
        "ClipboardEvent": ["clipboardData"],
        "CompositionEvent": ["data"],
        "DragEvent": ["dataTransfer"],
        "FocusEvent": ["relatedTarget"],
        "InputEvent": ["data", "isComposing"],
        "KeyboardEvent": ["code", "key", "location", "repeat", "which"],
        "MouseEvent": ["altKey", "button", "buttons", "clientX", "clientY", "ctrlKey", "metaKey", "movementX",
            "movementY", "offsetX", "offsetY", "pageX", "pageY", "region", "screenX", "screenY", "shiftKey"],
        "PointerEvent": ["height", "isPrimary", "pointerId", "pointerType", "pressure", "tangentialPressure",
            "tiltX", "tiltY", "twist", "width"],
        "ProgressEvent": ["lengthComputable", "loaded", "total"],
        "TouchEvent": ["altKey", "changedTouches", "ctrlKey", "metaKey", "shiftKey", "targetTouches", "touches"],
        "TransitionEvent": ["elapsedTime", "propertyName", "pseudoElement"],
        "UIEvent": ["detail", "view"],
        "WheelEvent": ["deltaMode", "deltaX", "deltaY", "deltaZ", "deltaMode"]
    };

    Object.keys(window).forEach(key => {
        if (/^on/.test(key)) {
            window.addEventListener(key.slice(2), event => {
                let properties = JSON.parse(JSON.stringify(proto_events));
                if (proto_subevent[event.constructor.name]) {
                    properties = properties.concat(proto_subevent[event.constructor.name]);
                }
                kromblast_signal(key, JSON.stringify(event, properties));
            });
        }
    });
})()
)