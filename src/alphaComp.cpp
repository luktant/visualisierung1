//vor der Schleife wo alle Samples durchgegangen werden
glm::vec4 alphaCompRGBA_a = {0,0,0,0};

//Alpha-Compositing
					else if (rendering == ALPHACOMP){
						//Transferfunktion, kann beliebig geändert werden
						glm::vec4 alphaCompRGBA_b = { 0, value, 0, value };
						float alpha_c = alphaCompRGBA_a[3] + (1 - alphaCompRGBA_a[3])*alphaCompRGBA_b[3];
						glm::vec4 alphaCompRGBA_c = { 0, 0, 0, alpha_c };
						alphaCompRGBA_c = 1 / alpha_c * (alphaCompRGBA_a[3] * alphaCompRGBA_a + (1 - alphaCompRGBA_a[3])*alphaCompRGBA_b[3] * alphaCompRGBA_b);
						
						//alphaCompRGBA_a ist der Wert der am Ende ausgegeben werden soll
						alphaCompRGBA_a = alphaCompRGBA_c;
						//wenn volle Transparenz erreicht, Suche abbrechen
						if (alphaCompRGBA_a[3] == 1)break;
					}