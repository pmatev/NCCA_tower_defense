#include "include/texturelib.h"
#include "QImage"
#include <iostream>

TextureLib* TextureLib::s_instance = 0;
//-------------------------------------------------------------------//
TextureLib::TextureLib()
{
}
//-------------------------------------------------------------------//
TextureLib::~TextureLib()
{
}
//-------------------------------------------------------------------//

TextureLib* TextureLib::instance()
{
    if(s_instance == 0)
    {
        s_instance = new TextureLib();
    }
    return s_instance;
}
//-------------------------------------------------------------------//
void TextureLib::destroy()
{
    if(s_instance)
    {
        delete s_instance;
    }
}
//-------------------------------------------------------------------//
void TextureLib::init()
{
    load("debug", "textures/default_texture.png");
    load("healthbar", "textures/HealthBar_flat.png");
    load("startMenuButton", "textures/startMenuButton_700x150.png");
    load("settingsMenuButton", "textures/settingsMenuButton");
    load("backToStartMenuButton", "textures/backToStartMenuButton.png");
    load("restartMenuButton", "textures/restartMenuButton.png");
    load("quitGameMenuButton", "textures/quitGameMenuButton.png");
    load("grenadeButton", "textures/grenadeButton.png");
    load("grenadeButtonNoMoney", "textures/grenadeButtonNoMoney.png");
    load("machineGunButton", "textures/machineGun.png");
    load("machineGunButtonNoMoney", "textures/machineGunNoMoney.png");
    load("wallButton", "textures/wallButton.png");
    load("wallButtonNoMoney", "textures/wallButtonNoMoney");
    load("playButton", "textures/playButton.png");
    load("pauseButton", "textures/pauseButton.png");
    load("sellButton", "textures/sellButton.png");
    load("settingButton", "textures/settingsButton.png");
    load("upgrade2BulletImage", "textures/upgrade2BulletImage.png");
    load("upgrade2GrenadeImage", "textures/upgrade2GrenadeImage.png");
    load("upgradeButton", "textures/upgradeButton.png");
    load("upgradeButtonNoMoney","textures/upgradeButtonNoMoney");
    load("background", "textures/backgroundTexture.png");
    load("closeButton", "textures/closeButton.png");
    load("createBackground","textures/createBackground.png");
    load("sellBulletImage", "textures/sellBulletImage.png");
    load("sellGrenadeImage", "textures/sellGrenadeImage.png");
    load("backToGameButton", "textures/closeMenuButton.png");

}
//-------------------------------------------------------------------//
void TextureLib::load(const std::string &_name, const std::string &_file)
{
    Texture t(_file);

    m_mapTextureIDs[_name] = t.getID();

}
//-------------------------------------------------------------------//
void TextureLib::bindTexture(const std::string &_name)
{
    if(m_mapTextureIDs[_name])
    {
        glBindTexture(GL_TEXTURE_2D, m_mapTextureIDs[_name]);
        m_boundTexture = _name;
    }
    else
    {
        std::cout<<"Couldn't bind texture "<<_name<<std::endl;
    }
}
//-------------------------------------------------------------------//
void TextureLib::bindTexture(const GLuint &_id)
{
    glBindTexture(GL_TEXTURE_2D, _id);
}

