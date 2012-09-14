
import processing.video.*;
import com.google.zxing.*;
import java.awt.image.BufferedImage;

String lastWrittenTextInFile;

Capture cam; //Set up the camera
com.google.zxing.Reader reader = new com.google.zxing.qrcode.QRCodeReader();

int WIDTH = 640;
int HEIGHT = 480;

int currentQRCodeNotFoundInterval = 0;

static final int kQR_CODE_NOT_FOUND_INTERVAL = 30;

boolean isQRCodeOnScreen;


PrintWriter fileOutput;

PImage cover;  //This will have the cover image
String lastISBNAcquired = "";  //This is the last ISBN we acquired

// Grabs the image file    

void closeTextFile()
{
//  fileOutput.flush();
//  fileOutput.close();
}

void writeTextToFile(String textToWrite)
{
  if (!textToWrite.equals(lastWrittenTextInFile))
  {  
    String[] strings = new String[1];
    strings[0] = textToWrite;
  
    saveStrings("nouns.txt", strings);
  
//   fileOutput.println(textToWrite);

    lastWrittenTextInFile = textToWrite;
    println("File written");
  }
}

void setTextFileBlank()
{
  if (!lastWrittenTextInFile.equals(""))  
  {
    String[] strings = new String[1];
    strings[0] = "";
  
    saveStrings("nouns.txt", strings);
  
    lastWrittenTextInFile = "";
    println("File blanked.");
  }
}

void exit()
{
  closeTextFile();
  super.exit();
}
  

void setup() {
  
  frameRate(20);
  size(640, 480);
  cam = new Capture(this, WIDTH, HEIGHT);
  
  fileOutput = createWriter("readID.txt");
  lastWrittenTextInFile = "";
  isQRCodeOnScreen = false;
}
 

void draw() {
  if (cam.available() == true) {
    cam.read();    
    image(cam, 0,0);
    
    try {
       // Now test to see if it has a QR code embedded in it
       LuminanceSource source = new BufferedImageLuminanceSource((BufferedImage)cam.getImage());
       BinaryBitmap bitmap = new BinaryBitmap(new HybridBinarizer(source));       
       Result result = reader.decode(bitmap); 
       
       
       
       //Once we get the results, we can do some display
       if (result.getText() != null) { 
         
         isQRCodeOnScreen = true;
          println(result.getText());
          writeTextToFile(result.getText());

          
          ResultPoint[] points = result.getResultPoints();
          //Draw some ellipses on at the control points
          for (int i = 0; i < points.length; i++) {
            fill(#ff8c00);
            ellipse(points[i].getX(), points[i].getY(), 20,20);
          }
          //Now fetch the book cover, if it is found
          if (!result.getText().equals(lastISBNAcquired)) {
             String url = "http://covers.oreilly.com/images/" + result.getText() + "/cat.gif";
             try {
                cover = loadImage(url,"gif");
                lastISBNAcquired = result.getText();
             } catch (Exception e) {
               cover = null;
             }
          }
          //Superimpose the cover on the image
          if (cover != null) {
            image(cover, points[1].getX(), points[1].getY());
          }
       }
       
       else  // no QR Detected!
       {
         /*
         println("nada");
         
        if (isQRCodeOnScreen)
         {
           // QR Code has dissapeared
           setTextFileBlank();  
         }
         
         isQRCodeOnScreen = false;
         */
       }
    } catch (Exception e) 
    {
        if (e.toString().equals("com.google.zxing.NotFoundException"))
        {
          currentQRCodeNotFoundInterval++;
          
          if (currentQRCodeNotFoundInterval >= kQR_CODE_NOT_FOUND_INTERVAL)
          {
            setTextFileBlank();
            println("Perdimos el codigo");
            currentQRCodeNotFoundInterval = 0;
            
          }
        }
      
         //println(e.toString()); 
    }
  }
  
}


void keyPressed() {
  setTextFileBlank();
  
}

