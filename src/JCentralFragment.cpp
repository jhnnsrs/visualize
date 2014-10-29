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

void JCentralFragment::restart(){

	s = &allvectors[0];
	t = &allvectors[1];
	u = &allvectors[2];
	v = &allvectors[3];

}

void JCentralFragment::branch(int there){

	if (nvertices-3-there < 0 ) return;

	s = &allvectors[nvertices-3-there];
	t = &allvectors[nvertices-2-there];
	u = &allvectors[nvertices-1-there];
	v = &allvectors[nvertices-0-there];

	

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
	if (nvertices % 1000 == 0 ) {mesh.addColor(ofColor(ofRandom(0,255),ofRandom(0,255),ofRandom(0,255)));}
	else {mesh.addColor(ofColor(255,255,255,ofRandom(22,120)));}
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
	mesh.addIndex(u - np);

	mesh.addIndex(s - np);
	mesh.addIndex(t - np);
	mesh.addIndex(v - np);

	mesh.addIndex(s - np);
	mesh.addIndex(u - np);
	mesh.addIndex(v - np);

	mesh.addIndex(u - np);
	mesh.addIndex(t - np);
	mesh.addIndex(v - np);




	zeit = ofGetElapsedTimeMillis();
		
}

void JCentralFragment::setInitialPyramid(ofVec3f a, ofVec3f b , ofVec3f c  , ofVec3f d ) {

	// Add verteces
	mesh.addVertex(a);
	allvectors.push_back(a);
	//mesh.addColor(ofColor(255,0,0));

	mesh.addVertex(b);
	allvectors.push_back(b);
	//mesh.addColor(ofColor(0,255,0));

	mesh.addVertex(c);
	allvectors.push_back(c);
	//mesh.addColor(ofColor(0,0,255));

	mesh.addVertex(d);
	allvectors.push_back(d);
	//mesh.addColor(ofColor(255,0,255));

	mesh.addColor(ofColor(0,0,0,ofRandom(23,144)));
	mesh.addColor(ofColor(0,0,0,ofRandom(23,144)));
	mesh.addColor(ofColor(0,0,0,ofRandom(23,144)));
	mesh.addColor(ofColor(0,0,0,ofRandom(23,144)));

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

JFragment* JCentralFragment::collapse(JFragment* frag,int size,ofColor color,float alpha) {
	
	// TODO:  FRAGMENT SHOULD NOT BE ADDED TO vector of FRAGMENTS
	// Only collapse if JCentralFragment is large enough
	size -= 1;
	if ( size >= nvertices-size) { return frag; }

	// SEND TO FRAGMENT
	vector<ofVec3f> fragvectors;
	vector<ofColor> fragcolors;
	vector<int> fragindices;
	map<int,int> vectorreference;

	//
	int nindicesmesh = mesh.getNumIndices()-1;


	// Will look for all connected vertices to the four faces of each pyramid on the new fragment
	// while scanning the faces as triplets of indices. If new vertex is found it is added to fragvectors
	// and a new key (index of vertex in centralfigure) and value ( new index of vertex in fragment/fragvectors) is 
	// appended to the vectorreferencemap
	for (int i = (nindicesmesh - 12*size); i <= nindicesmesh; i++)
	{
		fragindices.push_back(mesh.getIndex(i));
		if (vectorreference.count(mesh.getIndex(i)) == 0){
			fragvectors.push_back(allvectors[mesh.getIndex(i)]);
			frag->mesh.addVertex(allvectors[mesh.getIndex(i)]);
			frag->mesh.addColor(ofColor(color.r,color.g,color.b,alpha));
			vectorreference[mesh.getIndex(i)] = fragvectors.end() - fragvectors.begin()-1;
		}
	}

	// Adding Indixes according to vectorreferencemap and deleting faces from old
	for (int i = 0; i < fragindices.end() - fragindices.begin(); i++)
	{	
		cout << vectorreference[fragindices[i]] <<endl;
		frag->mesh.addIndex(vectorreference[fragindices[i]]);
		mesh.removeIndex(nindicesmesh-i);
	}
	for (int i = 0; i <= size; i++)
	{
		mesh.removeVertex(nvertices);		
		mesh.removeColor(nvertices);
		allvectors.pop_back();
		nvertices--;
	}
	
	// SET DIRECTION

	v = &allvectors[nvertices];
	u = &allvectors[nvertices-1];
	t = &allvectors[nvertices-2];
	s = &allvectors[nvertices-3];

	ofVec3f n = (*t-*s).crossed(*u-*s);
	n = *v;

	frag->direction = n.normalized();
	/*
	ofMesh centralmesh = mesh.getMeshForIndices(nvertices-size,nvertices);
	frag->mesh = centralmesh;
*/
	/*cout << frag->mesh.getNumIndices() << " INDICES" <<endl;
	cout << frag->mesh.getNumVertices() << " VERTICES" << endl;*/

	return frag;

}