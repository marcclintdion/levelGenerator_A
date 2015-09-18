        //------------------------------------------------------------------------------------------                                                       
        #ifdef __APPLE__                                                                                                                                   
        //---------------                                                                                                                                  
        filePathName = [[NSBundle mainBundle] pathForResource:@"level_01_SECTION_A_DOT3" ofType:@"bmp"];                                           
        if(fileName != nil)                                                                                                                                
        {                                                                                                                                                  
                image = imgLoadImage([filePathName cStringUsingEncoding:NSASCIIStringEncoding]);                                                           
                glGenTextures(1, &level_01_SECTION_A_NORMALMAP);                                                                                       
                glBindTexture(GL_TEXTURE_2D, level_01_SECTION_A_NORMALMAP);                                                                            
                ConfigureAndLoadTexture(image->data,  image->width, image->height );                                                                       
                imgDestroyImage(image);                                                                                                                    
           fileName = nil;                                                                                                                                 
        }else                                                                                                                                              
            {                                                                                                                                              
               //add error file output here                                                                                                                
            }                                                                                                                                              
        //---------------------                                                                                                                            
        filePathName = [[NSBundle mainBundle] pathForResource:@"level_01_SECTION_A" ofType:@"png"];                                                
        if(fileName != nil)                                                                                                                                
        {                                                                                                                                                  
                image = imgLoadImage([filePathName cStringUsingEncoding:NSASCIIStringEncoding]);                                                           
                glGenTextures(1, &level_01_SECTION_A_TEXTUREMAP);                                                                                      
                glBindTexture(GL_TEXTURE_2D, level_01_SECTION_A_TEXTUREMAP);                                                                           
                ConfigureAndLoadTexture(image->data,  image->width, image->height );                                                                       
                imgDestroyImage(image);                                                                                                                    
           fileName = nil;                                                                                                                                 
        }else                                                                                                                                              
            {                                                                                                                                              
               //add error file output here                                                                                                                
            }                                                                                                                                              
        //---------------                                                                                                                                  
        #endif                                                                                                                                             
        //------------------------------------------------------------------------------------------                                                       
        #ifdef WIN32                                                                                                                                       
        loadTexture("_MODEL_FOLDERS_/level_01_SECTION_A/level_01_SECTION_A_DOT3.png",          level_01_SECTION_A_NORMALMAP);                
        loadTexture("_MODEL_FOLDERS_/level_01_SECTION_A/level_01_SECTION_A.png",               level_01_SECTION_A_TEXTUREMAP);               
        #endif                                                                                                                                             
        //------------------------------------------------------------------------------------------------------------//___LOAD_VBO                        
        #include    "level_01_SECTION_A.cpp"                                                                                                         
        glGenBuffers(1,              &level_01_SECTION_A_VBO);                                                                                         
        glBindBuffer(GL_ARRAY_BUFFER, level_01_SECTION_A_VBO);                                                                                         
        glBufferData(GL_ARRAY_BUFFER, sizeof(level_01_SECTION_A), level_01_SECTION_A, GL_STATIC_DRAW);                                             
        glBindBuffer(GL_ARRAY_BUFFER, 0);                                                                                                                  
        //------------------------------------------------------------------------------------------------------------                                     
        #include    "level_01_SECTION_A_INDICES.cpp"                                                                                                 
        glGenBuffers(1,              &level_01_SECTION_A_INDICES_VBO);                                                                                   
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, level_01_SECTION_A_INDICES_VBO);                                                                           
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(level_01_SECTION_A_INDICES), level_01_SECTION_A_INDICES, GL_STATIC_DRAW);                       
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);                                                                                                            
        //------------------------------------------------------------------------------------------------------------                                       
        //====================================================================================   
        level_01_SECTION_A_boundingBox[0] = -6.96981;
        level_01_SECTION_A_boundingBox[1] = 77.029;
        level_01_SECTION_A_boundingBox[2] = -1.95902;
        level_01_SECTION_A_boundingBox[3] = 7.23036;
        level_01_SECTION_A_boundingBox[4] = -16.7134;
        level_01_SECTION_A_boundingBox[5] = 0.759264;
        //====================================================================================   
        collisionBoxArray[boxCount][0] = -6.96981;
        collisionBoxArray[boxCount][1] = 77.029;
        collisionBoxArray[boxCount][2] = -1.95902;
        collisionBoxArray[boxCount][3] = 7.23036;
        collisionBoxArray[boxCount][4] = -16.7134;
        collisionBoxArray[boxCount][5] = 0.759264;
        collisionBoxArray[boxCount][6] = boxCount;
        boxCount++;
