#include "JCentralFragment.h";

JCentralFragment::JCentralFragment()
{
}

JCentralFragment::~JCentralFragment()
{
}

void JCentralFragment::init(){
	
	// Set Inital Size of Vertices
	nvertices = 0;

	mesh.enableIndices();
	mesh.setMode(OF_PRIMITIVE_TRIANGLES);

	setInitialPyramid(ofVec3f(0,0,0),ofVec3f(100,0,0),ofVec3f(50,86.6,0),ofVec3f(50,43.3,75));
}

void JCentralFragment::init(ofVec3f a, ofVec3f b, ofVec3f c , ofVec3f d ){
	
	// Set Inital Size of Vertices
	nvertices = 0;

	mesh.enableIndices();
	mesh.setMode(OF_PRIMITIVE_TRIANGLES);

	setInitialPyramid(a,b,c,d);
}

void JCentralFragment::update(){
	
	// Select random side
		
	nadded = 0 + (rand() % (int)(2 + 1));

	// Rotate pyramide so that the spawn side
	// can be interpreted as A,B,C (Base) and D
	// peak. The base is not considered a spawning
	// side, as this may mess with the 3d structure.

	if (nadded == 0){
		a = *s;
		b = *t;
		c = *u;
		d = *v;
	}
	if (nadded == 1){
		a = *t;
		b = *u;
		c = *s;
		d = *v;
	}
	if (nadded == 2){
		a = *u;
		b = *s;
		c = *t;
		d = *v;
	}

	// Calculate barycenter of base (z, with help of m)
	// normal vector (n) of base and hence the new peak of the
	// pyramid (newv)
	ofVec3f n,m,z,newv;
	
	n = (b-a).crossed(d-a);
	m = b + (d-b)/2;
	z = a + 0.666f*(m-a);

	float randomness = ofMap(ofSignedNoise(ofGetElapsedTimef(),z.x,z.y,z.z),-1,1,0,1)*200;
	newv = z + n.normalized()*randomness;

	// Dirty, because vectors in C++ do not allow pointers to elements,
	// within the vector when it allocates new memory. Reference and pointers
	// return garbage. Python <3 
	smod =  s - &allvectors[0];
	tmod =  t - &allvectors[0];
	umod =  u - &allvectors[0];
	vmod =  v - &allvectors[0];

	// Add vector to mesh
	mesh.addVertex(newv);
	/*mesh.addColor(ofColor(ofRandom(0,255),ofRandom(0,255),ofRandom(0,255)));*/
	mesh.addColor(ofColor(255,255,255,35));
	allvectors.push_back(newv);
	nvertices++;

	// Rereference pointers
	s = &allvectors[smod];
	t = &allvectors[tmod];
	u = &allvectors[umod];
	v = &allvectors[vmod];

		
		
	// Change to new pyramid, wuhu beautiful
		
	if (nadded == 0){
		u = t;
		t = s;
			
	}

	if (nadded == 1){
		u = u;
		t = t;
				 
	}

	if (nadded == 2){
		t = u;
		u = s;
	}

	s = v;
	v = &allvectors[nvertices];

	// Add sides (triangles) to the mesh

	ofVec3f *np = &allvectors[0];
	mesh.addIndex(s - np);
	mesh.addIndex(t - np);
	mesh.addIndex(v - np);

	mesh.addIndex(s - np);
	mesh.addIndex(u - np);
	mesh.addIndex(v - np);

	mesh.addIndex(u - np);
	mesh.addIndex(t - np);
	mesh.addIndex(v - np);

	mesh.addIndex(s - np);
	mesh.addIndex(t - np);
	mesh.addIndex(u - np);


	zeit = ofGetElapsedTimeMillis();
		
}

void JCentralFragment::setInitialPyramid(ofVec3f a, ofVec3f b , ofVec3f c  , ofVec3f d ) {

	// Add verteces
	mesh.addVertex(a);
	allvectors.push_back(a);
	mesh.addColor(ofColor(255,0,0));

	mesh.addVertex(b);
	allvectors.push_back(b);
	mesh.addColor(ofColor(0,255,0));

	mesh.addVertex(c);
	allvectors.push_back(c);
	mesh.addColor(ofColor(0,0,255));

	mesh.addVertex(d);
	allvectors.push_back(d);
	mesh.addColor(ofColor(255,0,255));

	nvertices = nvertices + 3;

	mesh.addTriangle(0,1,3);
	mesh.addTriangle(0,1,2);
	mesh.addTriangle(1,2,3);
	mesh.addTriangle(0,3,2);
	
	// Set Pointers to Initial Triangle
	s = &allvectors[0];
	t = &allvectors[1];
	u = &allvectors[2];
	v = &allvectors[3];

}

JFragment* JCentralFragment::collapse(JFragment* frag,int size) {

	vector<ofVec3f> vectors;
	vectors = mesh.getVertices();

	int s = vectors.end() - vectors.begin();
	if ( size > s) { size = 3; }

	for (int i = 0; i < size; i++)
	{
		frag->mesh.addVertex(vectors.at(nvertices-i));
		frag->mesh.addColor(ofColor(255,255,255,24));
	}

	// MAKE DIRECTION

	ofVec3f a = vectors.at(nvertices);
	ofVec3f b = vectors.at(nvertices-1);
	ofVec3f c = vectors.at(nvertices-2);

	ofVec3f n = (b-a).crossed(c-a);

	frag->direction = n.normalized();
	/*
	ofMesh centralmesh = mesh.getMeshForIndices(nvertices-size,nvertices);
	frag->mesh = centralmesh;
*/
	/*cout << frag->mesh.getNumIndices() << " INDICES" <<endl;
	cout << frag->mesh.getNumVertices() << " VERTICES" << endl;*/

	return frag;

}