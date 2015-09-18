                    if(floorTile_2m_NORMALMAP != 0)                                                                                                      
                    {                                                                                                                                              
                            glDeleteTextures(1, &floorTile_2m_NORMALMAP);                                                                                
                            floorTile_2m_NORMALMAP = 0;                                                                                                  
                    }                                                                                                                                              
                    if(floorTile_2m_TEXTUREMAP  != 0)                                                                                                    
                    {                                                                                                                                              
                            glDeleteTextures(1, &floorTile_2m_TEXTUREMAP);                                                                               
                            floorTile_2m_TEXTUREMAP  = 0;                                                                                                
                    }                                                                                                                                              
                    if(floorTile_2m_VBO  != 0)                                                                                                           
                    {                                                                                                                                              
                            glDeleteBuffers(1, &floorTile_2m_VBO);                                                                                       
                            floorTile_2m_VBO  = 0;                                                                                                       
                    }                                                                                                                                              
                    if(floorTile_2m_INDICES_VBO  != 0)                                                                                                   
                    {                                                                                                                                              
                            glDeleteBuffers(1, &floorTile_2m_INDICES_VBO);                                                                               
                            floorTile_2m_INDICES_VBO  = 0;                                                                                               
                    }                                                                                                                                              
