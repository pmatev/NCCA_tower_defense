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
        createTexture("debug", "textures/default_texture.png");
        createTexture("healthbar", "textures/HealthBar_flat.png");
        createTexture("startMenuButton", "textures/startMenuButton_700x150.png");
        createTexture("startMenuButtonHover", "textures/startMenuButton_700x150Hover.png");
        createTexture("settingsMenuButton", "textures/settingsMenuButton");
        createTexture("settingsMenuButtonHover", "textures/settingsMenuButtonHover");
        createTexture("backToStartMenuButton", "textures/backToStartMenuButton.png");
        createTexture("backToStartMenuButtonHover", "textures/backToStartMenuButtonHover.png");
        createTexture("restartMenuButton", "textures/restartMenuButton.png");
        createTexture("restartMenuButtonHover", "textures/restartMenuButtonHover.png");
        createTexture("quitGameMenuButton", "textures/quitGameMenuButton.png");
        createTexture("quitGameMenuButtonHover", "textures/quitGameMenuButtonHover.png");
        createTexture("backToGameButton", "textures/closeMenuButton.png");
        createTexture("backToGameButtonHover", "textures/closeMenuButtonHover.png");
        createTexture("grenadeButton", "textures/grenadeButton.png");
        createTexture("grenadeButtonCreation", "textures/grenadeButtonCreation.png");
        createTexture("grenadeButtonNoMoney", "textures/grenadeButtonNoMoney.png");
        createTexture("machineGunButton", "textures/machineGun.png");
        createTexture("machineGunButtonCreation", "textures/machineGunCreation.png");
        createTexture("machineGunButtonNoMoney", "textures/machineGunNoMoney.png");
        createTexture("wallButton", "textures/wallButton.png");
        createTexture("wallButtonCreation", "textures/wallButtonCreation.png");
        createTexture("wallButtonNoMoney", "textures/wallButtonNoMoney");
        createTexture("playButton", "textures/playButton.png");
        createTexture("pauseButton", "textures/pauseButton.png");
        createTexture("sellButton", "textures/sellButton.png");
        createTexture("settingButton", "textures/settingsButton.png");
        createTexture("settingButtonHover", "textures/settingsButtonHover.png");
        createTexture("upgrade2BulletImage", "textures/upgrade2BulletImage.png");
        createTexture("upgrade2GrenadeImage", "textures/upgrade2GrenadeImage.png");
        createTexture("upgradeButton", "textures/upgradeButton.png");
        createTexture("upgradeButtonNoMoney","textures/upgradeButtonNoMoney");
        createTexture("background", "textures/backgroundTexture.png");
        createTexture("closeButton", "textures/closeButton.png");
        createTexture("createBackground","textures/createBackground.png");
        createTexture("sellBulletImage", "textures/sellBulletImage.png");
        createTexture("sellGrenadeImage", "textures/sellGrenadeImage.png");

}
//-------------------------------------------------------------------//
void TextureLib::createTexture(const std::string &_name)
{
    m_mapTextures[_name] = Texture::create(_name);

}

//-------------------------------------------------------------------//

void TextureLib::createTexture(const std::string &_name, const std::string &_file)
{
    TexturePtr texture = Texture::create(_name, _file);
    m_mapTextures[_name] = texture;
}

//-------------------------------------------------------------------//
void TextureLib::bindTexture(const std::string &_name)
{
    if(m_mapTextures[_name])
    {
        TexturePtr t = m_mapTextures[_name];
        glBindTexture(GL_TEXTURE_2D, t->getID());
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

