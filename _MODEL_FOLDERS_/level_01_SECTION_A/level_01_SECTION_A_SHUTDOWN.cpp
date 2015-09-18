                    if(level_01_SECTION_A_NORMALMAP != 0)                                                                                                      
                    {                                                                                                                                              
                            glDeleteTextures(1, &level_01_SECTION_A_NORMALMAP);                                                                                
                            level_01_SECTION_A_NORMALMAP = 0;                                                                                                  
                    }                                                                                                                                              
                    if(level_01_SECTION_A_TEXTUREMAP  != 0)                                                                                                    
                    {                                                                                                                                              
                            glDeleteTextures(1, &level_01_SECTION_A_TEXTUREMAP);                                                                               
                            level_01_SECTION_A_TEXTUREMAP  = 0;                                                                                                
                    }                                                                                                                                              
                    if(level_01_SECTION_A_VBO  != 0)                                                                                                           
                    {                                                                                                                                              
                            glDeleteBuffers(1, &level_01_SECTION_A_VBO);                                                                                       
                            level_01_SECTION_A_VBO  = 0;                                                                                                       
                    }                                                                                                                                              
                    if(level_01_SECTION_A_INDICES_VBO  != 0)                                                                                                   
                    {                                                                                                                                              
                            glDeleteBuffers(1, &level_01_SECTION_A_INDICES_VBO);                                                                               
                            level_01_SECTION_A_INDICES_VBO  = 0;                                                                                               
                    }                                                                                                                                              
