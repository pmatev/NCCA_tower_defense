#include "boost/bind.hpp"
#include "boost/spirit.hpp"
#include <boost/foreach.hpp>

#include "include/mesh.h"

// make a namespace for our parser to save writing boost::spirit:: all the time
namespace spt=boost::spirit;

// syntactic sugar for specifying our grammar
typedef spt::rule<spt::phrase_scanner_t> srule;


//-------------------------------------------------------------------//
MeshPtr Mesh::create(const std::string& _file,
                     std::string _name)
{
  MeshPtr a(new Mesh(_file,
                     _name));
  return a;
}


Mesh::Mesh(const std::string& _file,
           std::string _name) : m_name(_name)
{
  loadObj(_file);
}

//----------------------------------------------------------------------------------------------------------------------
// parse a vertex
void Mesh::parseVertex(const char *_begin)
{
  std::vector<float> values;
  // here is the parse rule to load the data into a vector (above)
  srule vertex = "v" >> spt::real_p[spt::append(values)] >>
                        spt::real_p[spt::append(values)] >>
                        spt::real_p[spt::append(values)];
  // now parse the data
  spt::parse_info<> result = spt::parse(_begin, vertex, spt::space_p);
  // should check this at some stage
  Q_UNUSED(result);
  // and add it to our vert list in abstact mesh parent
  m_verts.push_back(ngl::Vec3(values[0],values[1],values[2]));
}


//----------------------------------------------------------------------------------------------------------------------
// parse a texture coordinate
void Mesh::parseTextureCoordinate(const char * _begin)
{
  std::vector<float> values;
  // generate our parse rule for a tex cord,
  // this can be either a 2 or 3 d text so the *rule looks for an additional one
  srule texcord = "vt" >> spt::real_p[spt::append(values)] >>
                          spt::real_p[spt::append(values)] >>
                          *(spt::real_p[spt::append(values)]);
  spt::parse_info<> result = spt::parse(_begin, texcord, spt::space_p);
  // should check the return values at some stage
  Q_UNUSED(result);

  // build tex cord
  // if we have a value use it other wise set to 0
  float vt3 = values.size() == 3 ? values[2] : 0.0f;
  m_tex.push_back(ngl::Vec3(values[0],values[1],vt3));
}

//----------------------------------------------------------------------------------------------------------------------
// parse a normal
void Mesh::parseNormal(const char *_begin)
{
  std::vector<float> values;
  // here is our rule for normals
  srule norm = "vn" >> spt::real_p[spt::append(values)] >>
                       spt::real_p[spt::append(values)] >>
                       spt::real_p[spt::append(values)];
  // parse and push back to the list
  spt::parse_info<> result = spt::parse(_begin, norm, spt::space_p);
  // should check the return values at some stage
  Q_UNUSED(result);
  m_norm.push_back(ngl::Vec3(values[0],values[1],values[2]));
}

//----------------------------------------------------------------------------------------------------------------------
// parse face
void Mesh::parseFace(const char * _begin)
{
  // ok this one is quite complex first create some lists for our face data
  // list to hold the vertex data indices
  std::vector<int> vec;
  // list to hold the tex cord indices
  std::vector<int> tvec;
  // list to hold the normal indices
  std::vector<int> nvec;

  // create the parse rule for a face entry V/T/N
  // so our entry can be always a vert, followed by optional t and norm seperated by /
  // also it is possible to have just a V value with no / so the rule should do all this
  srule entry = spt::int_p[spt::append(vec)] >>
    (
      ("/" >> (spt::int_p[spt::append(tvec)] | spt::epsilon_p) >>
       "/" >> (spt::int_p[spt::append(nvec)] | spt::epsilon_p)
      )
      | spt::epsilon_p
    );
  // a face has at least 3 of the above entries plus many optional ones
  srule face = "f"  >> entry >> entry >> entry >> *(entry);
  // now we've done this we can parse
 spt::parse(_begin, face, spt::space_p);

  int numVerts=vec.size();
  // so now build a face structure.
  Face f;
  // verts are -1 the size
  f.m_numVerts=numVerts-1;
  f.m_textureCoord=false;
  f.m_normals=false;
  // copy the vertex indices into our face data structure index in obj start from 1
  // so we need to do -1 for our array index
  BOOST_FOREACH(int i, vec)
  {
    f.m_vert.push_back(i-1);
  }

  // merge in texture coordinates and normals, if present
  // OBJ format requires an encoding for faces which uses one of the vertex/texture/normal specifications
  // consistently across the entire face.  eg. we can have all v/vt/vn, or all v//vn, or all v, but not
  // v//vn then v/vt/vn ...
  if(!nvec.empty())
  {
    if(nvec.size() != vec.size())
    {
     std::cerr <<"Something wrong with the face data will continue but may not be correct\n";
    }

    // copy in these references to normal vectors to the mesh's normal vector
    BOOST_FOREACH(int i, nvec)
    {
      f.m_norm.push_back(i-1);
    }
    f.m_normals=true;

  }

  //
  // merge in texture coordinates, if present
  //
  if(!tvec.empty())
  {
    if(tvec.size() != vec.size())
    {
     std::cerr <<"Something wrong with the face data will continue but may not be correct\n";
    }

    // copy in these references to normal vectors to the mesh's normal vector
    BOOST_FOREACH(int i, tvec)
    {
      f.m_tex.push_back(i-1);
    }

    f.m_textureCoord=true;

  }
// finally save the face into our face list
  m_face.push_back(f);
}

//Uses data in an obj to create a VAO.
void Mesh::loadObj(const std::string &_file)
{
  // here we build up our ebnf rules for parsing
    // so first we have a comment
    srule comment = spt::comment_p("#");

    // see below for the rest of the obj spec and other good format data
    // http://local.wasp.uwa.edu.au/~pbourke/dataformats/obj/

    // vertices rule v is a parse of 3 reals and we run the parseVertex function
    srule vertex= ("v"  >> spt::real_p >> spt::real_p >> spt::real_p) [bind(&Mesh::parseVertex,boost::ref(*this), _1)];
    /// our tex rule and binding of the parse function
    srule tex= ("vt" >> spt::real_p >> spt::real_p) [bind(&Mesh::parseTextureCoordinate, boost::ref(*this), _1)];
    // the normal rule and parsing function
    srule norm= ("vn" >> spt::real_p >> spt::real_p >> spt::real_p) [bind(&Mesh::parseNormal,boost::ref(*this), _1)];

    // our vertex data can be any of the above values
    srule vertex_type = vertex | tex | norm;

    // the rule for the face and parser
    srule  face = (spt::ch_p('f') >> *(spt::anychar_p))[bind(&Mesh::parseFace, boost::ref(*this), _1)];
    // open the file to parse
    std::ifstream in(_file.c_str());
    if (in.is_open() != true)
    {
      std::cout<<"FILE NOT FOUND !!!! "<<_file.c_str()<<"\n";
      //return false;

    }
    std::string str;
    // loop grabbing a line and then pass it to our parsing framework
    while(getline(in, str))
    {
      spt::parse(str.c_str(), vertex_type  | face | comment, spt::space_p);
    }
    // now we are done close the file
    in.close();

    // grab the sizes used for drawing later
    m_nVerts=m_verts.size();

    m_nNorm=m_norm.size();
    m_nTex=m_tex.size();
    m_nFaces=m_face.size();

    //Use the data to create the VAO.
    createVAO();
}

bool Mesh::isTriangular()
{
  for(unsigned int i=0; i<m_nFaces; ++i)
  {
    if (m_face[i].m_numVerts >3)
    {
      return false;
    }
  }
  return true;
}

// a simple structure to hold our vertex data
// had to move this outside the method as g++ complains about it
// clang doesn't have a problem tho
struct VertData
{
  GLfloat u; // tex cords
  GLfloat v; // tex cords
  GLfloat nx; // normal from obj mesh
  GLfloat ny;
  GLfloat nz;
  GLfloat x; // position from obj
  GLfloat y;
  GLfloat z;
};

void Mesh::createVAO()
{
// else allocate space as build our VAO
  m_dataPackType=0;
  if(isTriangular())
  {
    m_dataPackType=GL_TRIANGLES;
    std::cout <<"Doing Tri Data"<<std::endl;
  }
  // data is mixed of > quad so exit error
  if(m_dataPackType == 0)
  {
    std::cerr<<"Can only create VBO from all Triangle or ALL Quad data at present"<<std::endl;
    exit(EXIT_FAILURE);
  }

  std::vector<Renderer::vertData> boxData;
  Renderer::vertData d;

  int loopFaceCount=3;

  // loop for each of the faces
  for(unsigned int i=0;i<m_nFaces;++i)
  {
    // now for each triangle in the face (remember we ensured tri above)
    for(int j=0;j<loopFaceCount;++j)
    {

      // pack in the vertex data first
      d.x=m_verts[m_face[i].m_vert[j]].m_x;
      d.y=m_verts[m_face[i].m_vert[j]].m_y;
      d.z=m_verts[m_face[i].m_vert[j]].m_z;
      // now if we have norms of tex (possibly could not) pack them as well
      if(m_nNorm >0 && m_nTex > 0)
      {

        d.nx=m_norm[m_face[i].m_norm[j]].m_x;
        d.ny=m_norm[m_face[i].m_norm[j]].m_y;
        d.nz=m_norm[m_face[i].m_norm[j]].m_z;

        //d.u=m_tex[m_face[i].m_tex[j]].m_x;
        //d.v=m_tex[m_face[i].m_tex[j]].m_y;

      }
      // now if neither are present (only verts like Zbrush models)
      else if(m_nNorm ==0 && m_nTex==0)
      {
        d.nx=0;
        d.ny=0;
        d.nz=0;
        //d.u=0;
        //d.v=0;
      }
      // here we've got norms but not tex
      else if(m_nNorm >0 && m_nTex==0)
      {
        d.nx=m_norm[m_face[i].m_norm[j]].m_x;
        d.ny=m_norm[m_face[i].m_norm[j]].m_y;
        d.nz=m_norm[m_face[i].m_norm[j]].m_z;
        //d.u=0;
        //d.v=0;
      }
      // here we've got tex but not norm least common
      else if(m_nNorm ==0 && m_nTex>0)
      {
        d.nx=0;
        d.ny=0;
        d.nz=0;
        //d.u=m_tex[m_face[i].m_tex[j]].m_x;
        //d.v=m_tex[m_face[i].m_tex[j]].m_y;
      }
    boxData.push_back(d);
    }
  }

  m_boxData = boxData;

  //call to generate the bounding box

  //generateLsBBox(boxData);
  Renderer *render = Renderer::instance();

  render->createVAO(m_name, GL_TRIANGLES);
  VAOPtr vao =  render->getVAObyID(m_name);

  vao->bind();
  int meshSize = boxData.size();

  // now we have our data add it to the VAO, we need to tell the VAO the following
  // how much (in bytes) data we are copying
  // a pointer to the first element of data (in this case the address of the first element of the
  // std::vector
  vao->setData(meshSize*sizeof(VertData),boxData[0].x);
  // in this case we have packed our data in interleaved format as follows
  // u,v,nx,ny,nz,x,y,z
  // If you look at the shader we have the following attributes being used
  // attribute vec3 inVert; attribute 0
  // attribute vec2 inUV; attribute 1
  // attribute vec3 inNormal; attribure 2
  // so we need to set the vertexAttributePointer so the correct size and type as follows
  // vertex is attribute 0 with x,y,z(3) parts of type GL_FLOAT, our complete packed data is
  // sizeof(vertData) and the offset into the data structure for the first x component is 5 (u,v,nx,ny,nz)..x
  vao->setVertexAttributePointer(0,3,GL_FLOAT,sizeof(d),0);
  // uv same as above but starts at 0 and is attrib 1 and only u,v so 2
  vao->setVertexAttributePointer(1,3,GL_FLOAT,sizeof(d),3);


  // now we have set the vertex attributes we tell the VAO class how many indices to draw when
  // glDrawArrays is called, in this case we use buffSize (but if we wished less of the sphere to be drawn we could
  // specify less (in steps of 3))
  vao->setNumIndices(meshSize);
  // finally we have finished for now so time to unbind the VAO
  vao->unbind();
}
