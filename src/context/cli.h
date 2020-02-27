#ifndef CLI_H
#define CLI_H

#include <string>

#include "buffer.h"
#include "camera.h"
#include "render_helper.h"
#include "renderer.h"
#include "scenemanager.h"

#include "context.h"


struct ContextCLI : public Context
{
    ContextCLI();
    ContextCLI(CLIArgs cliArgs);

    virtual bool Initialize() override;
    virtual bool Execute() override;

    private:
        Buffer _outputBuffer;
        Camera _camera;
        TracerRenderer _renderer;
        SceneManager _scene;
        RenderGlobals _globals;
};

#endif // CLI_H
