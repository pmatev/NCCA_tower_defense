#include "text.h"
#include "window.h"
#include <SDL_ttf.h>
#include <ngl/Types.h>
#include <boost/lexical_cast.hpp>
#include "ngl/ShaderLib.h"
#include "texturelib.h"


Text::Text(ngl::Vec2 _pos,
           const char *_text,
           const char *_fontFile,
           int _ptsize,
           std::string _name
           ):

    UIElement(_pos, _name, TEXT,""),
    m_text(_text)
{
    setColour(255,255,255,1);
    setFont(_fontFile, _ptsize);
//    generateMesh();
}

//------------------------------------------------------------------//
Text::~Text()
{
  //currently using default destructor
}

//------------------------------------------------------------------//
void Text::setFont(const char *_fontFile,int _ptsize)
{

      m_font = TTF_OpenFont(_fontFile, _ptsize);

      if (m_font == NULL){
        std::cout<<"font could not be found"<<std::endl;
      }
}


//------------------------------------------------------------------//
void Text::setColour(char _rvalue, char _gvalue, char _bvalue, char _avalue)
{
    SDL_Color tmpColour = {_rvalue, _gvalue, _bvalue, _avalue};

    m_colour = tmpColour;
}

//------------------code taken and adapted from---------------------//

//http://content.gpwiki.org/index.php/SDL_ttf:Tutorials:Basic_Font_Rendering//


void Text::draw()
{

    ngl::ShaderLib *shader=ngl::ShaderLib::instance();
    Renderer *render = Renderer::instance();
    Window *window = Window::instance();

    VAOPtr v = render->getVAObyID(m_IDStr);

    (*shader)["UI"]->use();
  //    (*shader)["Colour"]->use();

  //  render->loadMatrixToShader(m_transformStack,"Colour");

  //  shader->setRegisteredUniform3f("Colour",1,1,1);

    float scaleX = 2.0/window->getScreenWidth();
    float scaleY = 2.0/window->getScreenHeight();

    shader->setShaderParam1f("xpos",m_pos.m_x);
    shader->setShaderParam1f("ypos",m_pos.m_y);
    shader->setShaderParam1f("scaleX",scaleX);
    shader->setShaderParam1f("scaleY",scaleY);
    shader->setShaderParam4f("colourSelect", 0,0,0,0);



    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    TextureLib *tex = TextureLib::instance();
    tex->bindTexture(m_name);

//    m_billboard->draw("UI");
    v->bind();
    v->draw();
    v->unbind();
}



//------------------code taken and adapted from---------------------//
//--------------------Jon Macey Camera Demo -----------------------//
//-------and http://www.idevgames.com/forums/thread-1565.html------//


void Text::generateMesh()
{

    SDL_Surface *textSurface;


    textSurface = TTF_RenderText_Blended(m_font, m_text, m_colour);
    SDL_LockSurface( textSurface);

    TextureLib *tex = TextureLib::instance();

    tex->createTexture(m_name);
    TexturePtr t = tex->getTexture(m_name).lock();

    SDL_PixelFormat *format = textSurface->format;

    t->loadData(textSurface->w, textSurface->h,format->BytesPerPixel, textSurface->pixels);
    //    glGenTextures(1, &m_textureID);
//    glBindTexture(GL_TEXTURE_2D, m_textureID);




//    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

//    glTexImage2D
//            (
//                GL_TEXTURE_2D,
//                0,
//                GL_RGBA,
//                textSurface->w,
//                textSurface->h,
//                0,
//                GL_BGRA,
//                GL_UNSIGNED_BYTE,
//                textSurface->pixels
//                );

    if(m_size.m_x != textSurface->w)
    {
//        m_size.m_x = textSurface->w;
//        m_size.m_y = textSurface->h;

//        m_billboard = Billboard::create(Billboard::b2D, ngl::Vec4(m_pos.m_x, m_pos.m_y,0,1),m_size.m_x, m_size.m_y);
        struct textVertData
        {
        ngl::Real x;
        ngl::Real y;
        ngl::Real u;
        ngl::Real v;
        };
        // we are creating a billboard with two triangles so we only need the
        // 6 verts, (could use index and save some space but shouldn't be too much of an
        // issue
        textVertData d[6];
        // load values for triangle 1
        d[0].x=0;
        d[0].y=0;
        d[0].u=0.0f;
        d[0].v=1.0f;

        d[1].x=textSurface->w;
        d[1].y=0;
        d[1].u=1.0f;
        d[1].v=1.0f;

        d[2].x=0;
        d[2].y=textSurface->h;
        d[2].u=0.0f;
        d[2].v=0.0f;
        // load values for triangle two
        d[3].x=0;
        d[3].y=textSurface->h;
        d[3].u=0.0f;
        d[3].v=0.0f;


        d[4].x=textSurface->w;
        d[4].y=0;
        d[4].u=1.0f;
        d[4].v=1.0f;


        d[5].x=textSurface->w;
        d[5].y=textSurface->h;
        d[5].u=1.0f;
        d[5].v=0.0f;

        Renderer *render = Renderer::instance();
        VAOPtr v =render->getVAObyID(m_IDStr);

        if(!v)
        {
            render->createVAO(m_IDStr, GL_TRIANGLES);
            v =render->getVAObyID(m_IDStr);
        }

        v->bind();
        int size = sizeof(textVertData);
        v->setData(6*size,d[0].x);
        v->setVertexAttributePointer(0,2,GL_FLOAT,size,0);
        v->setVertexAttributePointer(1,2,GL_FLOAT,size,2);
        v->setNumIndices(6);
        v->unbind();

        m_size.m_x = textSurface->w;
        m_size.m_y = textSurface->h;
    }


    SDL_UnlockSurface( textSurface );

    SDL_FreeSurface(textSurface);
}
