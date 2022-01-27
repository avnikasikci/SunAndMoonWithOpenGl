//Güneş ve Ay Hareketi
/*
Bu program bir kuyruklu yıldızın bakış açısından küçük bir güneş sistemi simülasyonu  yapmaktadır.
Programda sarı bir güneş ve mavi bir ay vardır; ay kendi ekseni
etrafında ve güneşin etrafında döner.
*/
#include"glew.h" 
#include"freeglut.h" 
#include<iostream> 

void myWireSphere(GLfloat radius, int slices, int stacks) {
	glPushMatrix();// 
	glRotatef(-90.0, 1.0, 0.0, 0.0);//x eksinde 90 derece dönmesi 
	glutWireSphere(radius, slices, stacks);//telle sarılmış şekilde bir küre  oluşturur. 
	glPopMatrix();
	//radius=Kürenin yarıçapı. 
	//slices=Z ekseni etrafındaki alt bölümlerin sayısı (boylam çizgilerine benzer) //stacks=Z ekseni boyunca alt bölümlerin sayısı (enlem çizgilerine benzer). glPopMatrix(); 
	//glPushMatrix, mevcut matrisi çoğaltarak mevcut matris yığınını birer birer  aşağı iter. 
	//Matris modlarının her biri için bir matris yığını vardır. 
	
}


/*
* Programda, global değişkenlerde mevcut "yıl" ve mevcut "gün"ün  kaydı tutulur. Aslında gezegeni güneş etrafında 5 derecelik artışlarla ("yıl")  döndürüyoruz ve gezegeni 10 derecelik artışlarla ("gün") kendi ekseni etrafında  döndürüyoruz.
*/
static int year = 0, day = 0;
//Matris modunun GL_MODELVIEW olduğunu varsayıyoruz.  
//Bir SwapBuffers çağrısıyla bitirilir çünkü ekranda görmemiz için. void display() { 
void display(){
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
glPushMatrix();
// Güneş çizimi: orijinde merkezlenmiş, yarıçapı 1 olan sarı bir küre. glColor3f(1.0, 1.0, 0.0); 
myWireSphere(1.0, 15, 15);
// Ay çizimi: ekseni için beyaz bir çizgi çizilir, güneşten 2 birim uzaklıkta,  //yarıçapı 0,2 olan mavi bir küre çizilir. 
glRotatef((GLfloat)year, 0.0, 1.0, 0.0);
glTranslatef(2.0, 0.0, 0.0);
glRotatef((GLfloat)day, 0.0, 1.0, 0.0);
glColor3f(0.0, 0.0, 1.0);
myWireSphere(0.2, 15, 15);
glColor3f(1, 1, 1);
glBegin(GL_LINES);
glVertex3f(0, -0.3, 0);
glVertex3f(0, 0.3, 0);
glEnd();
glPopMatrix();
glFlush();
glutSwapBuffers();
}
static GLfloat u = 0.0; // bakılan açı(kamera) konumu için eğri  parametresi 
static GLfloat du = 0.1; // her kareyi artırmak için artış değeri 
void timer(int v) {
	u += du;
	day = (day + 1) % 360;
	year = (year + 2) % 360;
	glLoadIdentity();
	//bir görüntüleme dönüşümü tanımlar 
	gluLookAt(20 * cos(u / 8.0) + 12, 5 * sin(u / 8.0) + 1, 10 * cos(u / 8.0) + 2, 0, 0, 0, 0, 1, 0);
	glutPostRedisplay();
	//Belirli bir milisaniye sayısı içinde tetiklenecek bir zamanlayıcı callback  fonksiyonudur. 
	glutTimerFunc(1000 / 60, timer, v);
}
/*
* Burada, 60 derecelik dikey görüş alanına, sistem penceresine düzgün bir  şekilde eşlenecek, 1.0'a yakın kırpma düzlemi mesafesine ve
40.0 uzak kırpma mesafesine sahip bir perspektif kamera ayarlıyoruz. */
void reshape(GLint w, GLint h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (GLfloat)w / (GLfloat)h, 1.0, 40.0);
	glMatrixMode(GL_MODELVIEW);
}
int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Güneş ve Ay");
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutTimerFunc(100, timer, 0);
	glEnable(GL_DEPTH_TEST);
	glutMainLoop();
}
