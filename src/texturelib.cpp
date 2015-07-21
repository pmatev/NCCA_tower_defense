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
        loadTexture("arrowDownButton", "textures/arrowDownButton.png");
        loadTexture("arrowDownButtonPressed", "textures/arrowDownButtonPressed.png");
        loadTexture("arrowDownButtonHover", "textures/arrowDownButton.png");
        loadTexture("arrowUpButton", "textures/arrowUpButton.png");
        loadTexture("arrowUpButtonPressed", "textures/arrowUpButtonPressed.png");
        loadTexture("arrowUpButtonHover", "textures/arrowUpButton.png");
        loadTexture("backToGame", "textures/backToGame.png");
        loadTexture("backToGameHover", "textures/backToGameHover.png");
        loadTexture("backToGamePressed", "textures/backToGamePressed.png");
        loadTexture("backToStart", "textures/backToStart.png");
        loadTexture("backToStartHover", "textures/backToStartHover.png");
        loadTexture("backToStartPressed", "textures/backToStartPressed.png");
        loadTexture("bulletButton", "textures/bulletButton.png");
        loadTexture("bulletButtonCreate", "textures/bulletButtonCreate.png");
        loadTexture("bulletButtonHover", "textures/bulletButtonHover.png");
        loadTexture("bulletButtonNoMoney", "textures/bulletButtonNoMoney.png");
        loadTexture("bulletButtonPressed", "textures/bulletButtonPressed.png");
        loadTexture("closeButton", "textures/closeButton.png");
        loadTexture("closeButtonHover", "textures/closeButton.png");
        loadTexture("closeButtonPressed", "textures/closeButton.png");
        loadTexture("grenadeButton", "textures/grenadeButton.png");
        loadTexture("grenadeButtonCreate", "textures/grenadeButtonCreate.png");
        loadTexture("grenadeButtonHover", "textures/grenadeButtonHover.png");
        loadTexture("grenadeButtonNoMoney", "textures/grenadeButtonNoMoney.png");
        loadTexture("grenadeButtonPressed", "textures/grenadeButtonPressed.png");
        loadTexture("pauseButton", "textures/pauseButton.png");
        loadTexture("pauseButtonHover", "textures/pauseButtonHover.png");
        loadTexture("pauseButtonPressed", "textures/pauseButtonPressed.png");
        loadTexture("playButton", "textures/playButton.png");
        loadTexture("playButtonHover", "textures/playButtonHover.png");
        loadTexture("playButtonPressed", "textures/playButtonPressed.png");
        loadTexture("quit", "textures/quit.png");
        loadTexture("quitHover", "textures/quitHover.png");
        loadTexture("quitPressed", "textures/quitPressed.png");
        loadTexture("restart", "textures/restart.png");
        loadTexture("restartHover", "textures/restartHover.png");
        loadTexture("restartPressed", "textures/restartPressed.png");
        loadTexture("sellBulletImage", "textures/sellBulletImage.png");
        loadTexture("sellButton", "textures/sellButton.png");
        loadTexture("sellButtonHover", "textures/sellButtonHover.png");
        loadTexture("sellButtonPressed", "textures/sellButtonPressed.png");
        loadTexture("sellGrenadeImage", "textures/sellGrenadeImage.png");
        loadTexture("settings", "textures/settings.png");
        loadTexture("settingsHover", "textures/settingsHover.png");
        loadTexture("settingsPressed", "textures/settingsPressed.png");
        loadTexture("settingsButton", "textures/settingsButton.png");
        loadTexture("settingsButtonHover", "textures/settingsButton.png");
        loadTexture("settingsButtonPressed", "textures/settingsButtonPressed.png");
        loadTexture("startGame", "textures/startGame.png");
        loadTexture("startGameHover", "textures/startGameHover.png");
        loadTexture("startGamePressed", "textures/startGamePressed.png");
        loadTexture("startScreen", "textures/startScreen.png");
        loadTexture("gameOverBackground", "textures/gameOverScreen");
        loadTexture("settingsBackground", "textures/settingsBackground.png");
        loadTexture("towerPanel", "textures/towerPanel_withAlpha.png");
        loadTexture("upgrade2BulletImage", "textures/upgrade2BulletImage.png");
        loadTexture("upgrade2GrenadeImage", "textures/upgrade2GrenadeImage.png");
        loadTexture("upgradeButton", "textures/upgradeButton.png");
        loadTexture("upgradeButtonHover", "textures/upgradeButtonHover.png");
        loadTexture("upgradeButtonPressed", "textures/upgradeButtonPressed.png");
        loadTexture("upgradeButtonNoMoney", "textures/upgradeButtonNoMoney.png");
        loadTexture("wallButton", "textures/wallButton.png");
        loadTexture("wallButtonCreate", "textures/wallButtonCreate.png");
        loadTexture("wallButtonHover", "textures/wallButtonHover.png");
        loadTexture("wallButtonNoMoney", "textures/wallButtonNoMoney.png");
        loadTexture("wallButtonPressed", "textures/wallButtonPressed.png");
        loadTexture("hexagon_AO", "textures/hexagon_AO.png");
        loadTexture("enemy_AO", "textures/enemy_AO.png");
        loadTexture("bg_tile", "textures/bg_tile.png");
        loadTexture("turret_base", "textures/tower_base_AO.png");
        loadTexture("turret_cannon", "textures/tower_top_AO.png");
        loadTexture("wall_AO", "textures/wall_AO.png");
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

