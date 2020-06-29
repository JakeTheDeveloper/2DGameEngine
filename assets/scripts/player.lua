Entity = {
    name = "player",
    layer = "player_layer",
    components = {
        TransformComponent = {
            x = 0,
            y = 0,
            width = 64,
            height = 64
        },
        SpriteComponent = {
            textureId = "player",
            numFrames = 1,
            animationSpeed = 1,
            hasDirection = false,
            isFixed = false
        },
        MouseControlComponent = {

        }
    }
}

