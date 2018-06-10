package com.example.piotr.lab5;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.graphics.Paint;
import android.util.AttributeSet;
import android.view.MotionEvent;
import android.view.SurfaceHolder;
import android.view.SurfaceView;

public class DrawingSurface extends SurfaceView implements SurfaceHolder.Callback, Runnable {
    private boolean isThreadWorking= false;
    private SurfaceHolder surfaceHolder;
    private Thread drawingThread;
    private Paint paint = new Paint();
    private Position currPos;
    private Position prevPos;
    private Bitmap bitmap= null;
    public static Canvas canvas= null;
    private final Object lock = new Object();

    public DrawingSurface(Context context, AttributeSet attributeSet) {
        super(context, attributeSet);
        this.surfaceHolder = getHolder();
        this.surfaceHolder.addCallback(this);
    }
    public void resumePainting(){
        this.drawingThread = new Thread(this);
        this.isThreadWorking=true;
        this.drawingThread.start();
    }
    public void pausePainting(){
        this.isThreadWorking=false;
    }
    @Override
    public boolean onTouchEvent(MotionEvent event){
        performClick();
        synchronized (this.lock){
            switch (event.getAction()){
                case MotionEvent.ACTION_DOWN:
                    Position startPos = new Position(event.getX(), event.getY());
                    this.paint.setColor(MainActivity.color);
                    this.paint.setStrokeWidth(10);
                    this.canvas.drawCircle(startPos.x, startPos.y, 10, paint);
                    this.prevPos = startPos;
                    return true;

                case MotionEvent.ACTION_UP:
                    this.canvas.drawCircle(prevPos.x, prevPos.y, 10, paint);
                    return true;

                case MotionEvent.ACTION_MOVE:
                    this.currPos = new Position(event.getX(), event.getY());
                    canvas.drawLine(this.prevPos.x, this.prevPos.y, this.currPos.x, this.currPos.y, paint);
                    this.prevPos = currPos;
                    return true;
                default:
                    break;
            }
        }
        return false;

    }


    @Override
    public boolean performClick(){
        return super.performClick();
    }

    @Override
    public void run(){
        while(this.isThreadWorking){
            Canvas canvas = null;
            try {
                synchronized (this.surfaceHolder) {
                    if (!this.surfaceHolder.getSurface().isValid()) continue;
                    canvas = this.surfaceHolder.lockCanvas(null);

                    synchronized (this.lock) {
                        if (this.isThreadWorking) {
                            if (MainActivity.clear == true) {

                                canvas.drawARGB(255, 255, 255, 255);
                                MainActivity.clear = false;
                            }
                            canvas.drawBitmap(this.bitmap, 0,0,null);
                        }
                    }
                }
            }
            finally
            {
                if(canvas!= null)
                {
                    this.surfaceHolder.unlockCanvasAndPost(canvas);
                }
            }
            try
            {
                Thread.sleep(1000/25);
            }
            catch(InterruptedException e){}

        }

    }
    @Override
    public void surfaceCreated(SurfaceHolder holder) {
        this.bitmap=Bitmap.createBitmap(getWidth(),getHeight(),Bitmap.Config.ARGB_8888);
        this.canvas=new Canvas(bitmap);
        this.canvas.drawARGB(255,255,255,255);
        this.resumePainting();
    }

    @Override
    public void surfaceChanged(SurfaceHolder holder, int format, int width, int height) {

    }

    @Override
    public void surfaceDestroyed(SurfaceHolder holder) {
        this.pausePainting();
    }

}
