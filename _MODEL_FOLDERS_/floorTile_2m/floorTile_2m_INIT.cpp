        //------------------------------------------------------------------------------------------                                                       
        #ifdef __APPLE__                                                                                                                                   
        //---------------                                                                                                                                  
        filePathName = [[NSBundle mainBundle] pathForResource:@"floorTile_2m_DOT3" ofType:@"png"];                                           
        if(filePathName != nil)                                                                                                                                
        {                                                                                                                                                  
                image = imgLoadImage([filePathName cStringUsingEncoding:NSASCIIStringEncoding]);                                                           
                glGenTextures(1, &floorTile_2m_NORMALMAP);                                                                                       
                glBindTexture(GL_TEXTURE_2D, floorTile_2m_NORMALMAP);                                                                            
                ConfigureAndLoadTexture(image->data,  image->width, image->height );                                                                       
                imgDestroyImage(image);                                                                                                                    
           filePathName = nil;                                                                                                                                 
        }else                                                                                                                                              
            {                                                                                                                                              
               //add error file output here                                                                                                                
            }                                                                                                                                              
        //---------------------                                                                                                                            
        filePathName = [[NSBundle mainBundle] pathForResource:@"floorTile_2m" ofType:@"png"];                                                
        if(filePathName != nil)                                                                                                                                
        {                                                                                                                                                  
                image = imgLoadImage([filePathName cStringUsingEncoding:NSASCIIStringEncoding]);                                                           
                glGenTextures(1, &floorTile_2m_TEXTUREMAP);                                                                                      
                glBindTexture(GL_TEXTURE_2D, floorTile_2m_TEXTUREMAP);                                                                           
                ConfigureAndLoadTexture(image->data,  image->width, image->height );                                                                       
                imgDestroyImage(image);                                                                                                                    
           filePathName = nil;                                                                                                                                 
        }else                                                                                                                                              
            {                                                                                                                                              
               //add error file output here                                                                                                                
            }                                                                                                                                              
        //---------------                                                                                                                                  
        #endif                                                                                                                                             
        //------------------------------------------------------------------------------------------                                                       
        #ifdef WIN32                                                                                                                                       
        loadTexture("_MODEL_FOLDERS_/floorTile_2m/floorTile_2m_DOT3.png",          floorTile_2m_NORMALMAP);                
        loadTexture("_MODEL_FOLDERS_/floorTile_2m/floorTile_2m.png",               floorTile_2m_TEXTUREMAP);               
        #endif                                                                                                                                             
        //------------------------------------------------------------------------------------------------------------//___LOAD_VBO                        
        #include    "floorTile_2m.cpp"                                                                                                         
        glGenBuffers(1,              &floorTile_2m_VBO);                                                                                         
        glBindBuffer(GL_ARRAY_BUFFER, floorTile_2m_VBO);                                                                                         
        glBufferData(GL_ARRAY_BUFFER, sizeof(floorTile_2m), floorTile_2m, GL_STATIC_DRAW);                                             
        glBindBuffer(GL_ARRAY_BUFFER, 0);                                                                                                                  
        //------------------------------------------------------------------------------------------------------------                                     
        #include    "floorTile_2m_INDICES.cpp"                                                                                                 
        glGenBuffers(1,              &floorTile_2m_INDICES_VBO);                                                                                   
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, floorTile_2m_INDICES_VBO);                                                                           
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(floorTile_2m_INDICES), floorTile_2m_INDICES, GL_STATIC_DRAW);                       
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);                                                                                                            
        //------------------------------------------------------------------------------------------------------------                                       
        //====================================================================================   
        floorTile_2m_boundingBox[0] = -10.4335;
        floorTile_2m_boundingBox[1] = 10.4335;
        floorTile_2m_boundingBox[2] = -5;
        floorTile_2m_boundingBox[3] = 0.38534;
        floorTile_2m_boundingBox[4] = -10;
        floorTile_2m_boundingBox[5] = 10.4284;
        //====================================================================================   
        collisionBoxArray[boxCount][0] = -10.4335;
        collisionBoxArray[boxCount][1] = 10.4335;
        collisionBoxArray[boxCount][2] = -5;
        collisionBoxArray[boxCount][3] = 0.38534;
        collisionBoxArray[boxCount][4] = -10;
        collisionBoxArray[boxCount][5] = 10.4284;
        collisionBoxArray[boxCount][6] = boxCount;
        boxCount++;
