#define var GLfloat
//####################################################################################################################

#ifdef WIN32
        #define   glGenerateMipmap       glGenerateMipmapEXT
        #define   glGenFramebuffers      glGenFramebuffersEXT
        #define   glBindFramebuffer      glBindFramebufferEXT
        #define   glFramebufferTexture2D glFramebufferTexture2DEXT
         
        #define   STRICT
        #define   WIN32_LEAN_AND_MEAN
        #include <windows.h>
        #include <iostream.h>
        #include <fstream.h>
        //using namespace std; //___used for string object

        //-----------------------------------------------------------------------------

        #include <GL/gl.h>

        #include "headerFiles/glext.h"
        #include "headerFiles/glext_Init_A.cpp"

        void InitGL(void);
        void RenderGL(void);
        void shutDownGL(void);
        void ProcessKeyboard(void);
                
        var  viewWidth;
        var  viewHeight;
        
        //----------------------------------------------------------------------
        GLfloat  PassMouseMovement[2];
        //-------------------------------
        var keys[256], keypressed[256];

        
        //=================================        
        //----------------------------------
        #include "cpp/WGL_ARB_multisample.h"
        //=====================================

        #include "headerFiles/VSync.h"
        
        #include <windows.h>

        void      ConfigureAndLoadTexture(GLubyte *textureData, GLint texWidth, GLint texHeight );
        #include "headerFiles/glaux.h"
        #include "headerFiles/FreeImage.h"
        #include "cpp/freeImage.cpp"
        //------------------------------------------
 
#endif

//####################################################################################################################
float   X3[100];
float   X4[100];
float   Y3[100];
float   Y4[100];

float   planeX3_inner[100];   ////left edge
float   planeX3_outer[100];   ////left edge
float   planeX4_inner[100];   ////right edge
float   planeX4_outer[100];   ////right edge
float   planeY3_inner[100];   ////bottom edge
float   planeY3_outer[100];   ////bottom edge
float   planeY4_inner[100];   ////top edge
float   planeY4_outer[100];   ////top edge

void CollisionCheck_LEFT(float X1, float X2, float Y1, float Y2, GLfloat model_ID);
void CollisionCheck_RIGHT(float X1, float X2, float Y1, float Y2, GLfloat model_ID);
void CollisionCheck_UP(float X1, float X2, float Y1, float Y2, GLfloat model_ID);
void CollisionCheck_DOWN(float X1, float X2, float Y1, float Y2, GLfloat model_ID);
//####################################################################################################################        
        
        
        
        GLfloat  PassTouchMovement[3];

//####################################################################################################################

#include <math.h>
  
//####################################################################################################################

#include "MATRIX_MATH.cpp"

//####################################################################################################################

//--------------------------------------------------------------------------------------------------------------
#define BUFFER_OFFSET(i) ((char *)0 + (i))
//----------------------------------------------------------------------------------------

        extern GLuint msaaFramebuffer;

        void RenderGL(void);
        void InitGL  (void);
        void shutDownGL(void);
      
        #ifdef __APPLE__
               var viewWidth;
               var viewHeight;
               GLuint  viewFramebuffer;
        #endif
          
        //-------------------------------------------------------------------------------


GLuint m_uiShadowMapTexture;
GLuint m_uiFrameBufferObject;

int fileName = 0;

//#########################################################################################################



void ConfigureAndLoadTexture(GLubyte *textureData, GLint texWidth, GLint texHeight )
{

        #ifdef __APPLE__
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        //glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_NEAREST);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texWidth, texHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureData);
        glGenerateMipmap(GL_TEXTURE_2D);
        #endif
        
        #ifdef WIN32
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri( GL_TEXTURE_2D, GL_GENERATE_MIPMAP_SGIS, GL_TRUE );
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texWidth, texHeight, 0, GL_BGRA, GL_UNSIGNED_BYTE, textureData);
        #endif
}

//===============================================================================================================================


var     modelView[16];
var     projection[16];
var     mvpMatrix[16];
var     mvpMatrixInverse[16];
var     lightMatrix[16];
var     moveSetMatrix[16];
var     ProjectionShadow[16];
var     modelViewShadow[16];
var     viewMatrix[16];

var     LightModelViewMatrix[16];


float   modelWorld[16];
float   LightView[16];
float   LightProjection[16];
float   modelViewInverse[16];

float   tempMatrix[16];

var     textureMatrix[16] = {   0.5f, 0.0f, 0.0f, 0.0f,
                                0.0f, 0.5f, 0.0f, 0.0f,
                                0.0f, 0.0f, 0.5f, 0.0f,
                                0.5f, 0.5f, 0.5f, 1.0f   };

var     inverseMatrix[16];


//============================================================================================================================

var     moveShadowPivot_Z = 0.0;



//---------------------------------------------------------------------------------------
var           fieldOfView                                      =    30.0;
var           adjustNearFar[]                                  =  {  0.1, 250.0 };
//---------------------------------------------------------------------------------------
var           moveSet[]                                        =  {  0.0, 0, 0.0, 1.0};
//---------------------------------------------------------------------------------------
var           eyepositionCamera[]                              =  {  0, 0.0, 0.0, 0.0};
//---------------------------------------------------------------------------------------
var           eyeposition[]                                    =  {  0, 6.75, 30.2, 0.0};
var           lookAt[]                                         =  {  0,  6.75, 0, 0.0};
var           rotateModelWithLeftMouse[]                       =  {  0, 0};
//---------------------------------------------------------------------------------------
var           upVector[]             	                       =  {  0.0, 1.0, 0.0};
//---------------------------------------------------------------------------------------



//===========================================================================================================================================
void CollisionTest(GLfloat leftEdge,            GLfloat rightEdge, 
                   GLfloat bottomEdge,          GLfloat topEdge, 
                   GLfloat farEdge,             GLfloat nearEdge, 
                   GLfloat model_ID,   
                   GLfloat velocity_X,          GLfloat velocity_Y,        GLfloat velocity_Z,
                   GLfloat bounceFactor_X,      GLfloat bounceFactor_Y,    GLfloat bounceFactor_Z,
                   GLfloat updateCollisionInfo
                  );

//===========================================================================================================================================

void setupTransforms_MainColor(void)
{
        LoadIdentity(modelView);
        LookAt(modelView,    eyeposition[0],
                             eyeposition[1],
                             eyeposition[2],
                             lookAt[0],
                             lookAt[1],
                             lookAt[2],
                             upVector[0],
                             upVector[1],
                             upVector[2]);
        
        //--------------------------------------------------------------------------------------
        LoadIdentity(viewMatrix);
        AssignMatrix(viewMatrix, modelView);
        InvertMatrix(viewMatrix, viewMatrix);
        //--------------------------------------------------------------------------------------
        Translate(modelView, moveSet[0] , moveSet[1] , moveSet[2] );
        Rotate(modelView, 1.0, 0.0, 0.0, PassMouseMovement[0]);
        Rotate(modelView, 0.0, 1.0, 0.0, PassMouseMovement[1]);
}
                               
//===========================================================================================================================================                               
                            
                            
var           collisionBoxArray[1000][20];                            
                            
                            
                            
                               //#####################################___SHADERS___######################################################                            
                               //====================================================================================
                               #include "_SHADERS/plastic/rubber/rubber_SHADER_GLOBALS.cpp"
                               //====================================================================================
                               //#####################################___MODELS___#######################################################
                               
                               #include "_MODEL_FOLDERS_/level_01_SECTION_A/level_01_SECTION_A_Globals.cpp"                                                                
                               //====================================================================================   
                               
                               //====================================================================================
                               #include "_MODEL_FOLDERS_/unit_cube/unit_cube_Globals.cpp"                                                                
                               //====================================================================================   
                               #include "_MODEL_FOLDERS_/floorTile_2m/floorTile_2m_Globals.cpp"                                                                
                               //====================================================================================                                                                
                               GLfloat     model_01_collisionInfo[20];
                               GLfloat     model_01_POSITION[]                  =  {  0.0, 0.0,  0.0, 1.0};
                               GLfloat     model_01_VELOCITY[]                  =  {  0.05, 0.05,  0.05, 1.0};
                               bool        model_01_skipNextTest                =    false;
                               //====================================================================================
                               const GLint NUMBER_OF_BACKGROUND_MODELS          =  50;
                               GLuint      boxCount                             =  0;
                               GLuint      selectedModel                        =  0;                               
                               
                               GLfloat     backGroundModel[NUMBER_OF_BACKGROUND_MODELS];
                               //GLfloat     backGroundModel_POSITION[NUMBER_OF_BACKGROUND_MODELS][3]; 
                               GLfloat     backGroundModel_VELOCITY[NUMBER_OF_BACKGROUND_MODELS][3];                                                                          
                               GLfloat     backGroundModel_SCALE[NUMBER_OF_BACKGROUND_MODELS][3];
                          
                               //====================================================================================                             
                               GLfloat     character_collisionInfo[20];
                               GLfloat     character_POSITION[]                 = {  0.0,  0.0,  0.0, 1.0};
                               GLfloat     character_VELOCITY[]                 = {  0.1,  0.1,  0.0, 1.0};
                               GLfloat     character_SCALE[]                    = {  1.0,  1.0,  1.0, 1.0};

                               //bool        characterCanMoveDOWN                 =  true;
                               //bool        characterCanMoveUP                   =  true;
                               //bool        characterCanMoveLEFT                 =  true;
                               //bool        characterCanMoveRIGHT                =  true;                               
                               GLfloat     gravity                              =  0.0;
                               GLfloat     jumpVelocity                         =  5.0; 
                               bool        characterJumpReset                   =  true;
                               GLuint      characterModel_ID                    =  0;



//####################################################################################################################################################
//====================================================================================================================================================
//====================================================================================================================================================
//####################################################################################################################################################


var shaderNumber = 0;

void SelectShader(var shaderNumber)
{
        
        //--------------------------------------------------------------------------------------
        if(shaderNumber == 26)
        {
                #include "_SHADERS/plastic/rubber/rubber_SHADER_RENDER.cpp"
        }
        //--------------------------------------------------------------------------------------
    
   
}

//####################################################################################################################################################
//====================================================================================================================================================
//====================================================================================================================================================
//####################################################################################################################################################


void InitGL( void )
{//__BEGIN_INIT__@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

        //==========================================================================
        #ifdef WIN32
            #include "cpp/setPixelFormat.cpp"
            #include "headerFiles/glext_Init_B.cpp"
            //-------------------------------------
            SetVSyncState(true);
            //-------------------------------------
            PassMouseMovement[0]        = rotateModelWithLeftMouse[0];
            PassMouseMovement[1]        = rotateModelWithLeftMouse[1];
        #endif
        
        srand(time(0));                 


        for(int i = 0; i < NUMBER_OF_BACKGROUND_MODELS; i++)
        {
              collisionBoxArray[i][0]   =  float((rand()% 10)-5) *1.1;   
              collisionBoxArray[i][1]   =  float((rand()% 10)-5) *1.1;       
              collisionBoxArray[i][2]   =  0.0;   
              
              collisionBoxArray[i][3]   =  0.0;  
              collisionBoxArray[i][4]   =  0.0;       
              collisionBoxArray[i][5]   =  0.0;                
              
              //--------------------------------------------------------------------
              backGroundModel_SCALE[i][6]      =  1.0;  
              backGroundModel_SCALE[i][7]      =  1.0;       
              backGroundModel_SCALE[i][8]      =  1.0;    
              
              boxCount++;
        } 

        //############################################################################
        character_POSITION[1]        = 6.0f;
        collisionBoxArray[0][0]      = character_POSITION[0];
        collisionBoxArray[0][1]      = character_POSITION[1];
        collisionBoxArray[0][2]      = character_POSITION[2];
        //--------------------
        collisionBoxArray[0][3]      = character_VELOCITY[0];        
        collisionBoxArray[0][4]      = character_VELOCITY[1];
        collisionBoxArray[0][5]      = character_VELOCITY[2];         
        //--------------------
        collisionBoxArray[0][6]      = character_SCALE[0];        
        collisionBoxArray[0][7]      = character_SCALE[1];
        collisionBoxArray[0][8]      = character_SCALE[2];           
        //----------------------------------------------------------------------                
        collisionBoxArray[0][9]      = boxCount;//CharacterModel_ID
        //----------------------------------------------------------------------        
        collisionBoxArray[0][10]      = 1.0;    //_LEFT_is_true
        collisionBoxArray[0][11]      = 1.0;    //_RIGHT_is_true
        collisionBoxArray[0][12]      = 1.0;    //_DOWN_is_true
        collisionBoxArray[0][13]      = 1.0;    //_UP_is_true
        
        //=====================================================
        character_collisionInfo[0]   = collisionBoxArray[0][0];           
        character_collisionInfo[1]   = collisionBoxArray[0][1];        
        character_collisionInfo[2]   = collisionBoxArray[0][2];        
        character_collisionInfo[3]   = collisionBoxArray[0][3];        
        character_collisionInfo[4]   = collisionBoxArray[0][4];        
        character_collisionInfo[5]   = collisionBoxArray[0][5];        
        character_collisionInfo[6]   = collisionBoxArray[0][6];        
        character_collisionInfo[7]   = collisionBoxArray[0][7];  
        character_collisionInfo[8]   = collisionBoxArray[0][8];          
        character_collisionInfo[9]   = collisionBoxArray[0][9];//CharacterModel_ID  
        //-----------------------------------------------------
        character_collisionInfo[10]   = collisionBoxArray[0][10];  //_LEFT_is_true      
        character_collisionInfo[11]   = collisionBoxArray[0][11];  //_RIGHT_is_true
        character_collisionInfo[12]   = collisionBoxArray[0][12];  //_DOWN_is_true        
        character_collisionInfo[13]   = collisionBoxArray[0][13];  //_UP_is_true     
        
        //---------------------------------
        characterModel_ID       = boxCount;
        boxCount++;

        //############################################################################
              collisionBoxArray[1][0]   =  0.2;  
              collisionBoxArray[1][1]   =  -.1;       
              collisionBoxArray[1][2]   =  0.0; 

        
        
        //=================================================================================================================
        #include "_SHADERS/plastic/rubber/rubber_SHADER_INIT.cpp"
        //====================================================================================
        #include "_MODEL_FOLDERS_/level_01_SECTION_A/level_01_SECTION_A_Init.cpp"               
        //====================================================================================          
        #include "_MODEL_FOLDERS_/unit_cube/unit_cube_Init.cpp"                                                                   
        //------------------------------------------------------- 
        #include "_MODEL_FOLDERS_/floorTile_2m/floorTile_2m_Init.cpp"                                                                   
        //====================================================================================                                                                
        
        #include "settings_BackgroundModels.cpp" 
        //==================================================================================== 
        //#################################################################################################################



        //#################################################################################################################

    glEnable(GL_DEPTH_TEST);
    //glDepthFunc(GL_LEQUAL);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //glAlphaFunc(GL_GREATER, 0.1);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    
    glDisable(GL_BLEND);
        
//====================================================================================================================================

    



}//__END_INIT__@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


//####################################################################################################################################################
//====================================================================================================================================================
//====================================================================================================================================================
//####################################################################################################################################################



void RenderGL(void)
{
 
        //========================================================================================================================================================        
        //---------------------------------------------------RETURN_TO_MAIN_FRAMEBUFFER____________________!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        //---------------------------------------------------RETURN_TO_MAIN_FRAMEBUFFER____________________!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        //========================================================================================================================================================        
        #ifdef __APPLE__    
             glBindFramebuffer(GL_FRAMEBUFFER, msaaFramebuffer);
        #endif    
        //========================================================================================================================================================        
        //---------------------------------------------------RETURN_TO_MAIN_FRAMEBUFFER____________________!!!!!!!!!!!!!!!!!!!!!!!!!!!!        
        //---------------------------------------------------RETURN_TO_MAIN_FRAMEBUFFER____________________!!!!!!!!!!!!!!!!!!!!!!!!!!!!          
        //========================================================================================================================================================
        
        
        //=======================================================================================================================
        glClearColor( 0.0f, 0.0f, 0.0f, 1.0 );
        glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
        glViewport(0, 0, (GLsizei)viewWidth, (GLsizei)viewHeight);
        PerspectiveMatrix(projection, fieldOfView, (GLfloat)viewWidth / (GLfloat)viewHeight, adjustNearFar[0],  adjustNearFar[1]);
        //-------------------------------------------------------------------------------------------------------          

        
        //====================================================================================================================================                 
        //====================================================================================================================================                           
        //====================================================================================================================================
        
        shaderNumber = 26;//plastic/rubber/
        setupTransforms_MainColor();        
        rubber_SHININESS = 1.0; 
        Translate(modelView, character_POSITION[0], character_POSITION[1], character_POSITION[2]);                           
        #include "_MODEL_FOLDERS_/unit_cube/unit_cube_Render.cpp"                                                                 
        //====================================================================================================================================                 
        //====================================================================================================================================                           
        //====================================================================================================================================

        for(int i = 0; i < boxCount; i++)
        {
                if(selectedModel == i)
                {
                        rubber_SHININESS = 2.0;
                }
                else
                     {
                             rubber_SHININESS = 1.0;                   
                     }               
                
                
                setupTransforms_MainColor(); 
                Translate(modelView, collisionBoxArray[i][0], collisionBoxArray[i][1], collisionBoxArray[i][2]);                           
                Scale(modelView,     backGroundModel_SCALE[i][6],    backGroundModel_SCALE[i][7],    backGroundModel_SCALE[8][2]);                   
                #include "_MODEL_FOLDERS_/unit_cube/unit_cube_Render.cpp"  
        }

 
        //####################################################################################################################
        //####################################################################################################################
       
        CollisionCheck_DOWN(character_POSITION[0]-0.5, character_POSITION[0]+0.5, character_POSITION[1]-0.5, character_POSITION[1]+0.5, collisionBoxArray[0][9]);
        if(collisionBoxArray[0][12] == 1.0)   //object_can_move_down        
        {      
                
                collisionBoxArray[0][2]  -= gravity;//character_POSITION 
                        
                //----------------------------------
                gravity += 0.02;
        }
        //---------------------------------------------------------------------------------------------------------------------
        CollisionCheck_UP(character_POSITION[0]-0.5, character_POSITION[0]+0.5, character_POSITION[1]-0.5, character_POSITION[1]+0.5, collisionBoxArray[0][9]);        
        if(collisionBoxArray[0][13] == 1.0)           
        {      
             
             collisionBoxArray[0][2] += jumpVelocity;//character_POSITION

        }
        if(jumpVelocity >= 0.0f)
        {
              jumpVelocity -= gravity;
        }
        if(jumpVelocity < 0.0f)
        {
              jumpVelocity = 0.0f;
        } 
       
        //####################################################################################################################    
        

       
        #include "collisionTesting.cpp"
       
        //====================================================================================                                                                
    glEnable(GL_BLEND);
        shaderNumber = 26;//plastic/rubber/
        setupTransforms_MainColor();         
        rubber_SHININESS = 1.0;         
        #include "_MODEL_FOLDERS_/level_01_SECTION_A/level_01_SECTION_A_Render.cpp"         
    glDisable(GL_BLEND);
         
         
         
         
         
        //####################################################################################################################  
}//_END_RenderGL()


//####################################################################################################################################################
//====================================================================================================================================================
//====================================================================================================================================================
//####################################################################################################################################################


#ifdef WIN32
void ProcessKeyboard(void)
{
    
    //####################################################################################################### 
    if (keys['L'] && lKeyIsReset)
    {
            collisionBoxArray[selectedModel][0]  += 0.5;
            lKeyIsReset = false;
    }
    //--------------------------        
    if (!keys['L'])
    {
            lKeyIsReset = true;
    }    
    //=============================================================       
    if (keys['J'] && jKeyIsReset)
    {
            collisionBoxArray[selectedModel][0]  -= 0.5;
            jKeyIsReset = false;   
    }    
    //--------------------------        
    if (!keys['J'])
    {
            jKeyIsReset = true;
    }    
    //=============================================================    
    if (keys['I'] && iKeyIsReset)
    {
            collisionBoxArray[selectedModel][1]  += 0.5;
            iKeyIsReset = false;    
    } 
    //--------------------------        
    if (!keys['I'])
    {
            iKeyIsReset = true;
    }    
    //=============================================================    
    if (keys['K'] && kKeyIsReset)
    {
            collisionBoxArray[selectedModel][1]  -= 0.5;
            kKeyIsReset = false;      
    }
    //--------------------------        
    if (!keys['K'])
    {
            kKeyIsReset = true;
    }    
    //=============================================================    
    if (keys['O'] && oKeyIsReset)
    {
            collisionBoxArray[selectedModel][2]  += 0.5;
            oKeyIsReset = false;      
    }
    //--------------------------        
    if (!keys['O'])
    {
            oKeyIsReset = true;
    }    
    //=============================================================    
    if (keys['U'] && uKeyIsReset)  
    {
            collisionBoxArray[selectedModel][2]  -= 0.5;
            uKeyIsReset = false;      
    }
    //--------------------------        
    if (!keys['U'])
    {
            uKeyIsReset = true;
    }    
    //=============================================================    
    //####################################################################################################### 
    //======================================__SCALE_MODEL=======================================
    if (keys['X'] && xKeyIsReset)
    {
            backGroundModel_SCALE[selectedModel][6]  += 0.5;
            xKeyIsReset = false;
    }
    //--------------------------        
    if (!keys['X'])
    {
            xKeyIsReset = true;
    }    
    //=============================================================
    if (keys['Z'] && zKeyIsReset)
    {
            backGroundModel_SCALE[selectedModel][7]  -= 0.5;
            zKeyIsReset = false;
    }
    //--------------------------        
    if (!keys['Z'])
    {
            zKeyIsReset = true;
    }     
    //=============================================================
    if (keys['V'] && vKeyIsReset)
    {
             backGroundModel_SCALE[selectedModel][7] += 0.5;
             vKeyIsReset = false;   
    }
    //--------------------------        
    if (!keys['V'])
    {
            vKeyIsReset = true;
    }     
    //=============================================================
    if (keys['C'] && cKeyIsReset)
    {
             backGroundModel_SCALE[selectedModel][7] -= 0.5;
             cKeyIsReset = false;   
    }
    //--------------------------        
    if (!keys['C'])
    {
            cKeyIsReset = true;
    }     
    //=============================================================    
    
    if (keys['M'] && mKeyIsReset)
    {
             backGroundModel_SCALE[selectedModel][8] += 0.5;
             mKeyIsReset = false;   
    }
    //--------------------------        
    if (!keys['M'])
    {
            mKeyIsReset = true;
    }     
    //=============================================================
    if (keys['N'] && nKeyIsReset)
    {
             backGroundModel_SCALE[selectedModel][8] -= 0.5;
             nKeyIsReset = false;   
    }
    //--------------------------        
    if (!keys['N'])
    {
            nKeyIsReset = true;
    }     
    //=============================================================        
    
    
    
    //======================================__SCALE_MODEL=======================================   
    //#######################################################################################################
    //======================================__SELECT_MODEL======================================  
    if (keys[VK_OEM_PERIOD] && VK_OEM_PERIOD_KeyIsReset)
    {
             selectedModel += 1;
             VK_OEM_PERIOD_KeyIsReset = false;   
    }
    //--------------------------        
    if (!keys[VK_OEM_PERIOD])
    {
             VK_OEM_PERIOD_KeyIsReset = true;
    }    
    //=============================================================    
    if (keys[VK_OEM_COMMA] && VK_OEM_COMMA_KeyIsReset)
    {
             selectedModel -= 1;
             VK_OEM_COMMA_KeyIsReset = false;   
    }
    //--------------------------        
    if (!keys[VK_OEM_COMMA])
    {
             VK_OEM_COMMA_KeyIsReset = true;
    }     
    //======================================__SELECT_MODEL__======================================        
    //#######################################################################################################
    //======================================__ADD_MODEL__=========================================      
    
    //##############################################################################################################################################    
    if (keys[VK_HOME] && homeKeyIsReset)
    {
         //=========================================================================================================================================
         ofstream outSettings("settings_BackgroundModels.cpp");
         //----------------------------------------------------
         for(int i = 1; i < boxCount; i++)
         {
             outSettings << "//==========================================================================================  "             <<  "\n";            
             outSettings << "collisionBoxArray[" << i << "][0] =  " <<  collisionBoxArray[i][0]                            <<  ";\n";         
             outSettings << "collisionBoxArray[" << i << "][1] =  " <<  collisionBoxArray[i][1]                            <<  ";\n";          
             outSettings << "collisionBoxArray[" << i << "][2] =  " <<  collisionBoxArray[i][2]                            <<  ";\n";          
             outSettings << "//------------------------------------------------------------------------------  "                         <<  "\n"; 
             outSettings << "collisionBoxArray[" << i << "][3] =  " <<  collisionBoxArray[i][3]                            <<  ";\n";         
             outSettings << "collisionBoxArray[" << i << "][4] =  " <<  collisionBoxArray[i][4]                            <<  ";\n";          
             outSettings << "collisionBoxArray[" << i << "][5] =  " <<  collisionBoxArray[i][5]                            <<  ";\n";          
             outSettings << "//------------------------------------------------------------------------------  "                         <<  "\n"; 
             outSettings << "collisionBoxArray[" << i << "][6]" << " =  " <<   collisionBoxArray[i][6]  <<  ";\n";                       
             outSettings << "collisionBoxArray[" << i << "][7]" << " =  " <<   collisionBoxArray[i][7]  <<  ";\n";                 
             outSettings << "collisionBoxArray[" << i << "][8]" << " =  " <<   collisionBoxArray[i][8]  <<  ";\n";                 
             //=======================================================================================================================================
             outSettings << "collisionBoxArray[" << i << "][9]" << " =  " <<   i  <<  ";\n";                 
             //=======================================================================================================================================
             outSettings << "collisionBoxArray[" << i << "][10]" << " =  " <<   collisionBoxArray[i][10]  <<  ";\n";                       
             outSettings << "collisionBoxArray[" << i << "][11]" << " =  " <<   collisionBoxArray[i][11]  <<  ";\n";                 
             outSettings << "collisionBoxArray[" << i << "][12]" << " =  " <<   collisionBoxArray[i][12]  <<  ";\n";                 
             outSettings << "collisionBoxArray[" << i << "][13]" << " =  " <<   collisionBoxArray[i][13]  <<  ";\n";               
             
             
             //=======================================================================================================================================         
             outSettings << "//boxCount                =  " <<  i                                                                   <<  ";\n";             
             outSettings << "boxCount++;"                                                                                                <<  "\n";           
         }    
             outSettings << "//==========================================================================================  "             <<  "\n"; 
             outSettings << "selectedModel           =  " <<  selectedModel                                                              <<  ";\n";          
             //-----------------------------------------------------------
             outSettings << "eyeposition[0]          =  " <<  eyeposition[0]                                                             <<  ";\n";           
             outSettings << "eyeposition[1]          =  " <<  eyeposition[1]                                                             <<  ";\n";          
             outSettings << "eyeposition[2]          =  " <<  eyeposition[2]                                                             <<  ";\n";             
             //-----------------------------------------------------------
             outSettings << "lookAt[0]               =  " <<  lookAt[0]                                                                  <<  ";\n";           
             outSettings << "lookAt[1]               =  " <<  lookAt[1]                                                                  <<  ";\n";          
             outSettings << "lookAt[2]               =  " <<  lookAt[2]                                                                  <<  ";\n";          
         //=========================================================================================================================================   
             
             boxCount      += 1;
             selectedModel   += 1; 
             homeKeyIsReset = false;   
    }
    //##############################################################################################################################################    
    
    //--------------------------        
    if (!keys[VK_HOME])
    {
             homeKeyIsReset = true;
    } 
    //=============================================================     
    
    //##############################################################################################################################################
    if (keys[VK_END])
    {
        
         //=========================================================================================================================================
         ofstream outSettings("settings_BackgroundModels.cpp");
         //----------------------------------------------------
         
         for(int i = 1; i < boxCount; i++)
         {
             outSettings << "//==========================================================================================  "             <<  "\n";            
             outSettings << "collisionBoxArray[" << i << "][0] =  " <<  collisionBoxArray[i][0]                            <<  ";\n";         
             outSettings << "collisionBoxArray[" << i << "][1] =  " <<  collisionBoxArray[i][1]                            <<  ";\n";          
             outSettings << "collisionBoxArray[" << i << "][2] =  " <<  collisionBoxArray[i][2]                            <<  ";\n";          
             outSettings << "//------------------------------------------------------------------------------  "                         <<  "\n"; 
             outSettings << "collisionBoxArray[" << i << "][3] =  " <<  collisionBoxArray[i][3]                            <<  ";\n";         
             outSettings << "collisionBoxArray[" << i << "][4] =  " <<  collisionBoxArray[i][4]                            <<  ";\n";          
             outSettings << "collisionBoxArray[" << i << "][5] =  " <<  collisionBoxArray[i][5]                            <<  ";\n";          
             outSettings << "//------------------------------------------------------------------------------  "                         <<  "\n"; 
             outSettings << "collisionBoxArray[" << i << "][6]" << " =  " <<   collisionBoxArray[i][6]  <<  ";\n";                       
             outSettings << "collisionBoxArray[" << i << "][7]" << " =  " <<   collisionBoxArray[i][7]  <<  ";\n";                 
             outSettings << "collisionBoxArray[" << i << "][8]" << " =  " <<   collisionBoxArray[i][8]  <<  ";\n";                 
             //=======================================================================================================================================
             outSettings << "collisionBoxArray[" << i << "][9]" << " =  " <<   i  <<  ";\n";                 
             //=======================================================================================================================================
             outSettings << "collisionBoxArray[" << i << "][10]" << " =  " <<   collisionBoxArray[i][10]  <<  ";\n";                       
             outSettings << "collisionBoxArray[" << i << "][11]" << " =  " <<   collisionBoxArray[i][11]  <<  ";\n";                 
             outSettings << "collisionBoxArray[" << i << "][12]" << " =  " <<   collisionBoxArray[i][12]  <<  ";\n";                 
             outSettings << "collisionBoxArray[" << i << "][13]" << " =  " <<   collisionBoxArray[i][13]  <<  ";\n";               
             
             
             //=======================================================================================================================================         
             outSettings << "//boxCount                =  " <<  i                                                                   <<  ";\n";             
             outSettings << "boxCount++;"                                                                                                <<  "\n";           
         }   
             outSettings << "//==========================================================================================  "             <<  "\n"; 
             outSettings << "selectedModel           =  " <<  selectedModel                                                              <<  ";\n";          
             //-----------------------------------------------------------
             outSettings << "eyeposition[0]          =  " <<  eyeposition[0]                                                             <<  ";\n";           
             outSettings << "eyeposition[1]          =  " <<  eyeposition[1]                                                             <<  ";\n";          
             outSettings << "eyeposition[2]          =  " <<  eyeposition[2]                                                             <<  ";\n";             
             //-----------------------------------------------------------
             outSettings << "lookAt[0]               =  " <<  lookAt[0]                                                                  <<  ";\n";           
             outSettings << "lookAt[1]               =  " <<  lookAt[1]                                                                  <<  ";\n";          
             outSettings << "lookAt[2]               =  " <<  lookAt[2]                                                                  <<  ";\n";          
         //=========================================================================================================================================  
    
    
    }
    //##############################################################################################################################################    
    
    //======================================__ADD_MODEL__=========================================   
    //#######################################################################################################
    //======================================__UPDATE_SET__========================================   
    
    if (keys[VK_DELETE])
    {
      //  #include "settings_BackgroundModels.cpp"  
    }    
    
    //======================================__UPDATE_SET__========================================      
    //#######################################################################################################
    
    
    //####################################################################################################### 
    
    
    
    //==================================================================================================================================
/*    if(keys[VK_END])
    {
         ofstream outSettings("settings_BackgroundModels.cpp");
             
         
         for(int i = 0; i < boxCount; i++)
         {
             outSettings << "//==========================================================================================  "             <<  "\n";            
             outSettings << "collisionBoxArray[" << i << "][0] =  " <<  collisionBoxArray[i][0]                            <<  ";\n";         
             outSettings << "collisionBoxArray[" << i << "][1] =  " <<  collisionBoxArray[i][1]                            <<  ";\n";          
             outSettings << "collisionBoxArray[" << i << "][2] =  " <<  collisionBoxArray[i][2]                            <<  ";\n";          
             outSettings << "//------------------------------------------------------------------------------  "                         <<  "\n"; 
             outSettings << "backGroundModel_SCALE[" << i << "][0]    =  " <<  backGroundModel_SCALE[i][0]                               <<  ";\n";           
             outSettings << "backGroundModel_SCALE[" << i << "][1]    =  " <<  backGroundModel_SCALE[i][1]                               <<  ";\n";          
             outSettings << "backGroundModel_SCALE[" << i << "][2]    =  " <<  backGroundModel_SCALE[i][2]                               <<  ";\n";          
             outSettings << "//==========================================================================================  "             <<  "\n";         
             outSettings << "selectedModel    =  " <<  selectedModel                               <<  ";\n";          
         }
         
         //------------------------------------------------------------------------------------------------------------------------------         
             
             
             
         //------------------------------------------------------------------------------------
         
         
    }
*/
    if (!keys[VK_SPACE]) 			
    {
        spaceBarIsPressed = false;
        jumpVelocity      = 0.0f;
    }
    
    if (keys[VK_SPACE] && !spaceBarIsPressed && characterJumpReset && collisionBoxArray[0][12] == 1.0) 			
    {
        //if(jumpVelocity < 0.1f)
        gravity = 0.0f;
        jumpVelocity = 0.7f;
        characterJumpReset = false;
        if(jumpVelocity >= 1.1f)
        {
             spaceBarIsPressed  = true;
             
        } 
        spaceBarIsPressed = true;    
    } 

    //====================================================================================================================================
    if (keys[VK_LEFT])
    {     
          CollisionCheck_LEFT(character_POSITION[0]-0.5, character_POSITION[0]+0.5, character_POSITION[1]-0.5, character_POSITION[1]+0.5, collisionBoxArray[0][9]);
 
          if(collisionBoxArray[0][10] == 1.0)  
          {
                character_POSITION[0]    -= 0.07;
                collisionBoxArray[0][0]  -= 0.07;
                collisionBoxArray[0][1]  -= 0.07;
          }   
    }  
    //========================================================================================================================
    if (keys[VK_RIGHT])
    {
          CollisionCheck_RIGHT(character_POSITION[0]-0.5, character_POSITION[0]+0.5, character_POSITION[1]-0.5, character_POSITION[1]+0.5, collisionBoxArray[0][9]);
           
          if(collisionBoxArray[0][11] == 1.0)  
          {            
                character_POSITION[0]    += 0.07;
                collisionBoxArray[0][0]  += 0.07;
                collisionBoxArray[0][1]  += 0.07;          
          }                     
    }  
    //========================================================================================================================
    if (keys[VK_DOWN])
    {

          
    }  
    //========================================================================================================================
    if (keys[VK_UP])
    {

                               
    }  
    //========================================================================================================================
  
    if (keys['R']) 			
	{
        character_POSITION[1] = 6.0f;
        gravity = 0.0f;
    }  
   
//##########################################################################################################################   
    if (keys['D'] && !keys[VK_SHIFT])
    {
             eyeposition[0]         +=  0.15;
             lookAt[0]              +=  0.15;    
    }
    if (keys['A'] && !keys[VK_SHIFT])
    {
             eyeposition[0]         -=  0.15;
             lookAt[0]              -=  0.15;    
    }    
    if (keys['W'] && !keys[VK_SHIFT])
    {
             eyeposition[1]         +=  0.15;
             lookAt[1]              +=  0.15;     
    } 
    if (keys['S'] && !keys[VK_SHIFT])
    {
             eyeposition[1]         -=  0.15;
             lookAt[1]              -=  0.15;    
    }
    if (keys['E'] && !keys[VK_SHIFT])
    {
             eyeposition[2]         +=  0.15;
             lookAt[2]              +=  0.15;    
    }
    if (keys['Q'] && !keys[VK_SHIFT])  
    {
             eyeposition[2]         -=  0.15;
             lookAt[2]              -=  0.15;     
    }
//##########################################################################################################################

}//_END_ProcessKeyboard()
#endif




//####################################################################################################################################################
//====================================================================================================================================================
//====================================================================================================================================================
//####################################################################################################################################################


void CollisionCheck_LEFT(float X1, float X2, float Y1, float Y2, GLfloat model_ID)           //////*****************************************
{
    //characterCanMoveLEFT = true;

    for( int i = 0; i < boxCount; i++)
    {
         collisionBoxArray[0][10] = 1.0;//character can move left = true(1.0)
         //-----------------------------------------------
         planeX3_inner[i] = collisionBoxArray[i][0] + 0.05f;   ////left edge
         planeX3_outer[i] = collisionBoxArray[i][0] - 0.05f;   ////left edge
         planeX4_inner[i] = collisionBoxArray[i][1] - 0.05f;   ////right edge
         planeX4_outer[i] = collisionBoxArray[i][1] + 0.05f;   ////right edge
         planeY3_inner[i] = collisionBoxArray[i][2] + 0.05f;   ////bottom edge
         planeY3_outer[i] = collisionBoxArray[i][2] - 0.05f;   ////bottom edge
         planeY4_inner[i] = collisionBoxArray[i][3] - 0.05f;   ////top edge
         planeY4_outer[i] = collisionBoxArray[i][3] + 0.05f;   ////top edge

        if((X2 >= collisionBoxArray[i][0]) && (collisionBoxArray[i][1]+character_VELOCITY[0] >= X1) && (Y2 >= collisionBoxArray[i][2]) && (collisionBoxArray[i][3] >= Y1))   
        {
                                
                                collisionBoxArray[0][10] = 0.0;//character can move LEFT = FALSE
                                //------------------------------------------------------------------------
                                if((Y2 >= planeY3_outer[i]) && (Y2 <= planeY3_inner[i]) && (X2 >= planeX3_outer[i]) && (X1 <= planeX4_outer[i]) && (collisionBoxArray[0][10] == 0.0))/////___CLEARS STICKY EDGES
                                        collisionBoxArray[0][10] = 1.0;//character can move LEFT = TRUE                       /////top edge of moving primary object
                                //------------------------------------------------------------------------
                                if((Y1 <= planeY4_outer[i]) && (Y1 >= planeY4_inner[i]) && (X2 >= planeX3_outer[i]) && (X1 <= planeX4_outer[i]) && (collisionBoxArray[0][10] == 0.0))/////___CLEARS STICKY EDGES
                                        collisionBoxArray[0][10] = 1.0;//character can move LEFT = TRUE                      /////bottom edge of moving primary object
                                //------------------------------------------------------------------------
                                if((X2 >= planeX3_outer[i]) && (X2 <= planeX4_inner[i]) && (Y2 >= planeY3_outer[i]) && (Y1 <= planeY4_outer[i]) && (collisionBoxArray[0][10] == 0.0))/////___CLEARS STICKY EDGES
                                        collisionBoxArray[0][10] = 1.0;//character can move LEFT = TRUE
                                //------------------------------------------------------------------------
                                if(model_ID == i)
                                {
                                        collisionBoxArray[0][10] = 1.0; //TESTS AGAINST SELF COLLISION
                                }  
                                //------------------------------------------------------------------------
                                if(collisionBoxArray[0][10] == 0.0)//if character can move LEFT == false
                                {
                                        //collisionObjectIdentifier = i;
                                        break;
                                }
                                //------------------------------------------------------------------------
        }
    }        
}

void CollisionCheck_RIGHT(float X1, float X2, float Y1, float Y2, GLfloat model_ID)          //////*****************************************
{
     //characterCanMoveRIGHT = true;
  
     for( int i = 0; i < boxCount; i++)
     {
          collisionBoxArray[0][11] = 1.0;//character can move right = true(1.0)
          //-----------------------------------------------------------
          planeX3_inner[i] = collisionBoxArray[i][0] + 0.05f;   ////left edge
          planeX3_outer[i] = collisionBoxArray[i][0] - 0.05f;   ////left edge
          planeX4_inner[i] = collisionBoxArray[i][1] - 0.05f;   ////right edge
          planeX4_outer[i] = collisionBoxArray[i][1] + 0.05f;   ////right edge
          planeY3_inner[i] = collisionBoxArray[i][2] + 0.05;   ////bottom edge
          planeY3_outer[i] = collisionBoxArray[i][2] - 0.05f;   ////bottom edge
          planeY4_inner[i] = collisionBoxArray[i][3] - 0.05f;   ////top edge
          planeY4_outer[i] = collisionBoxArray[i][3] + 0.05f;   ////top edge
     
          if((X2 >= collisionBoxArray[i][0]-character_VELOCITY[0]) && (collisionBoxArray[i][1] >= X1) && (Y2 >= collisionBoxArray[i][2]) && (collisionBoxArray[i][3] >= Y1))
          {       
                                 collisionBoxArray[0][11] = 0.0;//character can move RIGHT = FALSE
                                 //------------------------------------------------------------------------     
                                 if((Y2 >= planeY3_outer[i]) && (Y2 <= planeY3_inner[i]) && (X2 >= planeX3_outer[i]) && (X1 <= planeX4_outer[i]) && (collisionBoxArray[0][11] == 0.0))/////___CLEARS STICKY EDGES//character can move right == false
                                         collisionBoxArray[0][11] = 1.0;//character can move RIGHT = TRUE                       /////top edge of moving primary object
                                 //------------------------------------------------------------------------      
                                 if((Y1 >= planeY4_inner[i]) && (Y1 <= planeY4_outer[i]) && (X2 >= planeX3_outer[i]) && (X1 <= planeX4_outer[i]) && (collisionBoxArray[0][11] == 0.0))/////___CLEARS STICKY EDGES//character can move right == false
                                         collisionBoxArray[0][11] = 1.0;//character can move RIGHT = TRUE                       /////bottom edge of moving primary object
                                 //------------------------------------------------------------------------       
                                 if((X1 >= planeX4_inner[i]) && (X1 <= planeX4_outer[i]) && (Y1 <= planeY4_outer[i]) && (Y2 >= planeY3_outer[i]) && (collisionBoxArray[0][11] == 0.0))/////___CLEARS STICKY EDGES//character can move right == false
                                         collisionBoxArray[0][11] = 1.0;//character can move RIGHT = TRUE
                                 //------------------------------------------------------------------------ 
                                 if(model_ID == i)
                                 {
                                         collisionBoxArray[0][11] = 1.0; //TESTS AGAINST SELF COLLISION
                                 }
                                 //------------------------------------------------------------------------  
                                 if(collisionBoxArray[0][11] == 0.0)//if character can move RIGHT == false
                                 {
                                         //collisionObjectIdentifier = i; 
                                         break;
                                 } 
                                 //------------------------------------------------------------------------
          }
     }  
}

void CollisionCheck_UP(float X1, float X2, float Y1, float Y2, GLfloat model_ID)             //////*****************************************
{
     
    
     for( int i = 0; i < boxCount; i++)
     {
        collisionBoxArray[i][13] = 1.0;//character can move up = true(1.0)
        //---------------------------------
        planeX3_inner[i] = collisionBoxArray[i][0] + 0.05f;   ////left edge
        planeX3_outer[i] = collisionBoxArray[i][0] - 0.05f;   ////left edge
        planeX4_inner[i] = collisionBoxArray[i][1] - 0.05f;   ////right edge
        planeX4_outer[i] = collisionBoxArray[i][1] + 0.05f;   ////right edge
        planeY3_inner[i] = collisionBoxArray[i][2] + 0.05f;   ////bottom edge
        planeY3_outer[i] = collisionBoxArray[i][2] - 0.05f;   ////bottom edge
        planeY4_inner[i] = collisionBoxArray[i][3] - 0.05f;   ////top edge
        planeY4_outer[i] = collisionBoxArray[i][3] + 0.05f;   ////top edge
     
        if((X2 >= collisionBoxArray[i][0]) && (collisionBoxArray[i][1] >= X1) && (Y2 >= collisionBoxArray[i][2]-jumpVelocity+gravity) && (collisionBoxArray[i][3] >= Y1))        
        {       
                               collisionBoxArray[i][13] = 0.0;//character can move UP = FALSE
                               //------------------------------------------------------------------------
                               if((X2 >= planeX3_outer[i]) && (X2 <= planeX3_inner[i]) && (Y1 <= planeY4_outer[i]) && (Y2 >= planeY3_outer[i]-jumpVelocity+gravity) && (collisionBoxArray[i][13] == 0.0))/////___CLEARS STICKY EDGES
                                       collisionBoxArray[i][13] = 1.0;//character can move UP = TRUE
                               //------------------------------------------------------------------------
                               if((X1 >= planeX4_inner[i]) && (X1 <= planeX4_outer[i]) && (Y1 <= planeY4_outer[i]) && (Y2 >= planeY3_outer[i]-jumpVelocity+gravity) && (collisionBoxArray[i][13] == 0.0))/////___CLEARS STICKY EDGES
                                       collisionBoxArray[i][13] = 1.0;//character can move UP = TRUE
                               //------------------------------------------------------------------------
                               if((Y1 >= planeY4_inner[i]) && (Y1 <= planeY4_outer[i]) && (X1 <= planeX4_outer[i]) && (X2 >= planeX3_outer[i]-jumpVelocity+gravity) && (collisionBoxArray[i][13] == 0.0))/////___CLEARS STICKY EDGES
                                       collisionBoxArray[i][13] = 1.0;//character can move UP = TRUE
                               //------------------------------------------------------------------------
                               if(model_ID == i)
                               {
                                       collisionBoxArray[i][13] = 1.0; //TESTS AGAINST SELF COLLISION
                               }
                               //------------------------------------------------------------------------
                               if(collisionBoxArray[i][13] == 0.0)//if character can move UP == false
                               {
                                       jumpVelocity = 0;
                                       //collisionObjectIdentifier = i;
                                       break;
                               }
                               //------------------------------------------------------------------------     
        }
     
     }   
}
//        collisionBoxArray[0][10]      = 1.0;    //_LEFT_is_true
//        collisionBoxArray[0][11]      = 1.0;    //_RIGHT_is_true
//        collisionBoxArray[0][12]      = 1.0;    //_DOWN_is_true
//        collisionBoxArray[0][13]      = 1.0;    //_UP_is_true

void CollisionCheck_DOWN(float X1, float X2, float Y1, float Y2, GLfloat model_ID)           //////*****************************************
{   
     
    //==============================================================
                                         if(model_ID == 0)//main character collision
                                         {     
                                               characterJumpReset = false;//prevents character from jumping in air after sliding off edge which was resetting jump
                                         }
                                         //==============================================================
     
     for( int i = 0; i < boxCount; i++)
     {
                    collisionBoxArray[i][12] = 1.0;//character can move down = true(1.0)
          //-------------------------------
          planeX3_inner[i] = collisionBoxArray[i][0] + 0.05f;   ////left edge
          planeX3_outer[i] = collisionBoxArray[i][0] - 0.05f;    ////left edge
          planeX4_inner[i] = collisionBoxArray[i][1] - 0.05f;   ////right edge
          planeX4_outer[i] = collisionBoxArray[i][1] + 0.05f;    ////right edge
          planeY3_inner[i] = collisionBoxArray[i][2] + 0.05f;   ////bottom edge 
          planeY3_outer[i] = collisionBoxArray[i][2] - 0.05f;   ////bottom edge
          planeY4_inner[i] = collisionBoxArray[i][3] - 0.05f;   ////top edge
          planeY4_outer[i] = collisionBoxArray[i][3] + 0.05f;   ////top edge
       
          if((X2 >= collisionBoxArray[i][0]) && (collisionBoxArray[i][1] >= X1) && (Y2 >= collisionBoxArray[i][2]) && (collisionBoxArray[i][3]+gravity >= Y1))
          {       
                                 collisionBoxArray[i][12] = 0.0;//character can move DOWN = FALSE                                                                        
                                 //------------------------------------------------------------------------
                                 if((X2 >= planeX3_outer[i]) && (X2 <= planeX3_inner[i]) && (Y1 <= planeY4_outer[i]) && (Y2 >= planeY3_outer[i]) && (collisionBoxArray[i][12] == 0.0))/////___CLEARS STICKY EDGES
                                         collisionBoxArray[i][12] = 1.0;//character can move DOWN = TRUE
                                 //------------------------------------------------------------------------
                                 if((X1 >= planeX4_inner[i]) && (X1 <= planeX4_outer[i]) && (Y1 <= planeY4_outer[i]) && (Y2 >= planeY3_outer[i]) && (collisionBoxArray[i][12] == 0.0))/////___CLEARS STICKY EDGES
                                         collisionBoxArray[i][12] = 1.0;//character can move DOWN = TRUE
                                 //------------------------------------------------------------------------
                                 if((Y2 >= planeY3_outer[i]) && (Y2 <= planeY3_inner[i]) && (X2 >= planeX3_outer[i]) && (X1 <= planeX4_outer[i]) && (collisionBoxArray[i][12] == 0.0))/////___CLEARS STICKY EDGES
                                         collisionBoxArray[i][12] = 1.0;//character can move DOWN = TRUE
                                 //------------------------------------------------------------------------
                                 if(model_ID == i)
                                 {
                                         collisionBoxArray[i][12] = 1.0; //TESTS AGAINST SELF COLLISION
                                 }
                                 //------------------------------------------------------------------------
                                 if(collisionBoxArray[i][12] == 0.0)//if character can move DOWN == false
                                 {      
                                         collisionBoxArray[i][12] = 0.0;//character can move DOWN = false
                                         //collisionObjectIdentifier = i;                                       
                                        
                                         if(model_ID == 0)//main character collision
                                         {
                                                 gravity = 0.0f;
                                                 characterJumpReset = true;
                                         }
                                        
                                         break;
                                 } 
                                 //------------------------------------------------------------------------    
          }   
      
     }        
}


//####################################################################################################################################################
//====================================================================================================================================================
//====================================================================================================================================================
//####################################################################################################################################################


void shutDownGL( void )
{
     //#####################################___SHADERS___######################################################      
     #include "_SHADERS/plastic/rubber/rubber_SHUTDOWN.cpp"
     //====================================================================================     
     //#####################################___MODELS___#######################################################      
     #include "_MODEL_FOLDERS_/unit_cube/unit_cube_Shutdown.cpp"                                                               
     //====================================================================================  
     #include "_MODEL_FOLDERS_/level_01_SECTION_A/level_01_SECTION_A_Shutdown.cpp"                                                               
     //====================================================================================   
   
}



