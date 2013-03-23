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
        loadTexture("debug", "textures/default_texture.png");
        loadTexture("healthbar", "textures/HealthBar_flat.png");
        m_mapTextures["healthbar"]->setWrap(GL_CLAMP_TO_EDGE);
        loadTexture("startMenuButton", "textures/startMenuButton_700x150.png");
        loadTexture("startMenuButtonHover", "textures/startMenuButton_700x150Hover.png");
        loadTexture("settingsMenuButton", "textures/settingsMenuButton");
        loadTexture("settingsMenuButtonHover", "textures/settingsMenuButtonHover");
        loadTexture("backToStartMenuButton", "textures/backToStartMenuButton.png");
        loadTexture("backToStartMenuButtonHover", "textures/backToStartMenuButtonHover.png");
        loadTexture("restartMenuButton", "textures/restartMenuButton.png");
        loadTexture("restartMenuButtonHover", "textures/restartMenuButtonHover.png");
        loadTexture("quitGameMenuButton", "textures/quitGameMenuButton.png");
        loadTexture("quitGameMenuButtonHover", "textures/quitGameMenuButtonHover.png");
        loadTexture("backToGameButton", "textures/closeMenuButton.png");
        loadTexture("backToGameButtonHover", "textures/closeMenuButtonHover.png");
        loadTexture("grenadeButton", "textures/grenadeButtonSmall.png");
        loadTexture("grenadeButtonCreation", "textures/grenadeButtonCreation.png");
        loadTexture("grenadeButtonNoMoney", "textures/grenadeButtonNoMoney.png");
        loadTexture("machineGunButton", "textures/machineGun.png");
        loadTexture("machineGunButtonCreation", "textures/machineGunCreation.png");
        loadTexture("machineGunButtonNoMoney", "textures/machineGunNoMoney.png");
        loadTexture("wallButton", "textures/wallButton.png");
        loadTexture("wallButtonCreation", "textures/wallButtonCreation.png");
        loadTexture("wallButtonNoMoney", "textures/wallButtonNoMoney");
        loadTexture("playButton", "textures/playButton.png");
        loadTexture("playButtonHover", "textures/playButton.png");
        loadTexture("pauseButton", "textures/pauseButton.png");
        loadTexture("sellButton", "textures/sellButton.png");
        loadTexture("settingButton", "textures/settingsButton.png");
        loadTexture("settingButtonHover", "textures/settingsButtonHover.png");
        loadTexture("upgrade2BulletImage", "textures/upgrade2BulletImage.png");
        loadTexture("upgrade2GrenadeImage", "textures/upgrade2GrenadeImage.png");
        loadTexture("upgradeButton", "textures/upgradeButton.png");
        loadTexture("upgradeButtonNoMoney","textures/upgradeButtonNoMoney");
        loadTexture("background", "textures/backgroundTexture.png");
        loadTexture("closeButton", "textures/closeButton.png");
        loadTexture("createBackground","textures/createBackground.png");
        loadTexture("sellBulletImage", "textures/sellBulletImage.png");
        loadTexture("sellGrenadeImage", "textures/sellGrenadeImage.png");
        loadTexture("hexagon_AO", "textures/hexagon_AO.png");
        loadTexture("enemy_AO", "textures/enemy_AO.png");
        loadTexture("bg_tile", "textures/bg_tile.png");

}

void TextureLib::createTexture(const std::string &_name)
{
    TexturePtr texture = Texture::create(_name);
    m_mapTextures[_name] = texture;
}

//-------------------------------------------------------------------//

void TextureLib::loadTexture(const std::string &_name, const std::string &_file)
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

