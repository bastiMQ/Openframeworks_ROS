#include "ofAppGLFWWindow.h"
#include "ofMain.h"
#include "ofxAssimpModelLoader.h"
#include "ofxFakeShadowMap.h"
#include "ofxGui.h"
#include "ofxCloth.h"

class ofApp : public ofBaseApp{

	public:
		ofPlanePrimitive plane;
		vector<Clothing> cloth;
                ofxFakeShadowMap shadow;
		ofEasyCam camera;
		ofLight pLight,sLight,dLight;
		ofMaterial material;
		ofxAssimpModelLoader model;
		
		ofxAssimpModelLoader model2;
		
	        ofMesh mesh0,mesh1;

	        ofMesh mesh20,mesh21;
	        
	        
		int counter = 0;
		int speedanim = 40;
	        float animationPosition;
		bool wire = false;
		bool stop = true;
		bool wind = false;
		int flg=0;
		void setup() {
			//ofSetSmoothLighting(true);
    			pLight.setDiffuseColor( ofColor(155.f, 255.f, 255.f));
        		pLight.setSpecularColor( ofColor(255.f, 255.f, 255.f));
		        pLight.setPointLight();
			sLight.setDiffuseColor( ofColor(255.f, 255.f, 255.f));
        		sLight.setSpecularColor( ofColor(255.f, 255.f, 255.f));
    			sLight.setSpotlight();
    			sLight.setSpotlightCutOff( 50 );
    			sLight.setSpotConcentration( 45 );
			dLight.setDiffuseColor(ofColor(255.f, 255.f, 255.f));
		        dLight.setSpecularColor(ofColor(255.f, 255.f, 255.f));
		        dLight.setDirectional();
        		dLight.setOrientation( ofVec3f(0, -90, -90) );
        		material.setShininess( 159 );
        		material.setSpecularColor(ofColor(250, 250, 255, 255));
			camera.setNearClip(.1);
			camera.setDistance(50);
			
			
			//for(int i = 0; i < 4; i++){
			//	Clothing clo;
			//	clo.setup((int)ofRandom(2,5),(int)ofRandom(25,40),35,35);
	               //         clo.constrainPoints( 1, ofVec3f(1,0,0) ) ;
			//        clo.constrainPoints( clo.getPlaneWidth()-1, ofVec3f(-1,0,0) ) ;
			//	cloth.push_back(clo);
			//}
			

			model.loadModel("model.dae",true);

			mesh0 = model.getMesh(0);
	                mesh1 = model.getMesh(1);

	                model2.setScale(0.055, 0.055, 0.055);
	              model2.loadModel("r2d2.obj",true);

			//mesh20 = model2.getMesh(0);



	                
			shadow.setup();
		        shadow.setColors(ofColor(0,0,0));
		        shadow.setAlpha(1.f);

			plane.set(50,50);
			plane.rotate(180,ofVec3f(0,1,1));
			
			ofSetBackgroundColor(255,255,255);
		}

		void update() {
			//ofSetWindowTitle(ofToString(ofGetFrameRate()));
			model.update();
	                animationPosition = ofMap(counter++,0,speedanim,0.0,1.0);
        	        if(counter>speedanim) counter=0;
	                model.setPositionForAllAnimations(animationPosition);
                	                
	                mesh0 = model.getCurrentAnimatedMesh(0);
	                mesh1 = model.getCurrentAnimatedMesh(1);

	                
		        //shadow.setDirLight(ofVec3f(0,0,0));
       			//for(int i = 0; i < cloth.size(); i++){	
		        //        cloth[i].update();
		        //        cloth[i].addForce( ofVec3f(ofRandom(-0.2,0.2),ofRandom(0.4,-0.4),0), ofRandom(-1.f,1.f) );
			//	cloth[i].windForce( ofVec3f(ofRandom(-0.2,0.2),0,ofRandom(0.4,0.65)), ofRandom(2,4) );
			//}
			
					        if(flg==1){
		        static int i=0;
		        
		       	char filename[]="./img/log_";
			char fileext[]="gif";
			char buf[1024];
			sprintf(buf, "%s%05d.%s",filename, i, fileext);
			string fname_out=buf;
			// ofImageを定義
			ofImage myImage;

			// myImageに画面のキャプチャを描画
			myImage.grabScreen(0, 0, ofGetWidth(), ofGetHeight());

			// myImageを書き出す
			myImage.saveImage(fname_out, OF_IMAGE_QUALITY_BEST);
			i++;
		        }
		        
		}

		void draw() {
		       // ofBackgroundGradient( ofColor(210), ofColor(10));

		        camera.begin();
			ofEnableDepthTest();
			//plane.draw();
			
			
			//	for(int x1=-75;x1<150;x1+=10){
			//				for(int y1=-75;y1<150;y1+=10){
			//ofLine(x1,y1,x1+150,y1+150);
			//	}
			//		}
			
			ofDisableDepthTest();

			render();

			shadow.begin(camera);
		                render();
		        shadow.end();



		        

		        camera.end();
		        
		        

		        
		}

		void render(){

			ofEnableLighting();
        		material.begin();
        		pLight.enable();
		        sLight.enable();
		        dLight.enable();
			ofEnableDepthTest();


			ofPushMatrix();

	                ofTranslate(10,-0,-25);
			ofRotateZ(180);
			ofRotateY(90);
			model2.drawVertices(); //モデルの頂点を描画
			model2.drawFaces();  //モデルの面を描画
			ofRotateY(-90);
			ofRotateZ(-180);
    	                ofTranslate(0,0,25);
    	                
    	         	ofPopMatrix();
			
			ofPushMatrix();       
    	                
			ofRotateY(-180);
			
			ofSetColor(0,0,200);
	                mesh0.draw();
	               	ofSetColor(0,200,100);
	                mesh1.draw();
	                
	                ofRotateY(-30);
	                ofTranslate(10,0,0);
			ofSetColor(0,200,0);
	                mesh0.draw();
	               	ofSetColor(0,200,100);
	                mesh1.draw();
	                
	                ofRotateY(-30);
	                ofTranslate(10,0,0);
			ofSetColor(0,200,0);
	                mesh0.draw();
	               	ofSetColor(0,200,100);
	                mesh1.draw();

	                ofRotateY(-30);
	                ofTranslate(10,0,0);
			ofSetColor(0,200,0);
	                mesh0.draw();
	               	ofSetColor(0,200,100);
	                mesh1.draw();

	                ofRotateY(-30);
	                ofTranslate(10,0,0);
			ofSetColor(0,200,0);
	                mesh0.draw();
	               	ofSetColor(0,200,100);
	                mesh1.draw();
	                
	                ofRotateY(-30);
	                ofTranslate(10,0,0);
			ofSetColor(0,200,0);
	                mesh0.draw();
	               	ofSetColor(0,200,100);
	                mesh1.draw();	                
	                	                                
			ofPopMatrix();
		
			ofPushMatrix();
	                ofTranslate(10,0,15);
			ofSetColor(0,200,0);
			ofRotateY(-180);
	                mesh0.draw();
	               	ofSetColor(0,200,100);
	                mesh1.draw();	
	       		ofPopMatrix();

			
			ofDisableLighting();
        		material.end();
        		pLight.disable();
		        sLight.disable();
		        dLight.disable();
			ofDisableDepthTest();
		}


		void keyPressed(int key) {
		        switch (key) {
				case 'w':
					flg=!flg;
					break;
				case 'd':
					wire=!wire;
					break;
				case 's':
					stop=!stop;
					break;
				case 'i':
					cloth.clear();
					for(int i = 0; i < 3; i++){
						Clothing clo;
						clo.setup((int)ofRandom(2,5),(int)ofRandom(25,40),(int)ofRandom(35,50),(int)ofRandom(35,50));
						clo.constrainPoints( 1, ofVec3f(1,0,0) ) ;
						clo.constrainPoints( clo.getPlaneWidth()-1, ofVec3f(-1,0,0) ) ;
						cloth.push_back(clo);
					}
					break;
		        }
		}
};

int main()
{
       ofSetupOpenGL(480,320, OF_WINDOW);
       ofRunApp( new ofApp());
}




