package com.led.led;

import android.graphics.Color;
import android.support.v7.app.ActionBarActivity;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuItem;
import android.bluetooth.BluetoothSocket;
import android.content.Intent;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.ImageButton;
import android.widget.SeekBar;
import android.widget.TextView;
import android.widget.Toast;
import android.app.ProgressDialog;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.os.AsyncTask;
import java.io.IOException;
import java.lang.String;
import java.util.UUID;

public class ledControl extends ActionBarActivity {

    Button btnOff, btnDis, btnS1, btnS2, btnS3, btnS4, btnS5, btnS6;
    SeekBar brightness, red, green, blue,ringnumber;
    TextView lumn, lumnred,lumngreen,lumnblue,l,r,g,b;
    ImageButton c1,c2,c3,c4,c5,c6,c7;
    String address = null;
    private ProgressDialog progress;
    BluetoothAdapter myBluetooth = null;
    BluetoothSocket Socket = null;
    private boolean isBtConnected = false;
    Integer pr_redR1=0,pr_redR2=0, pr_greenR1=0,pr_greenR2=0,pr_blueR1=0,pr_blueR2=0,pr_brightnessR1=10,pr_brightnessR2=10;
    Integer temp_ring=0;
    Integer temp_S1R1=0,temp_S2R1=0,temp_S3R1=0,temp_S4R1=0,temp_S5R1=0,temp_S6R1=0;
    Integer temp_S1R2=0,temp_S2R2=0,temp_S3R2=0,temp_S4R2=0,temp_S5R2=0,temp_S6R2=0;


    static final UUID myUUID = UUID.fromString("00001101-0000-1000-8000-00805F9B34FB");

    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);

        Intent newint = getIntent();
        address = newint.getStringExtra(DeviceList.EXTRA_ADDRESS); //receive the address of the bluetooth device

        //view of the ledControl
        setContentView(R.layout.activity_led_control);

        //call the widgtes
        btnOff = (Button)findViewById(R.id.button3);
        btnDis = (Button)findViewById(R.id.button4);
        btnS1 = (Button)findViewById(R.id.button5);
        btnS2 = (Button)findViewById(R.id.button6);
        btnS3 = (Button)findViewById(R.id.button7);
        btnS4 = (Button)findViewById(R.id.button8);
        btnS5 = (Button)findViewById(R.id.button9);
        btnS6 = (Button)findViewById(R.id.button10);
        brightness = (SeekBar)findViewById(R.id.seekBar);
        lumn = (TextView)findViewById(R.id.lumn);
        red = (SeekBar)findViewById(R.id.seekBar2);
        green = (SeekBar)findViewById(R.id.seekBar3);
        blue = (SeekBar)findViewById(R.id.seekBar4);
        lumnred = (TextView)findViewById(R.id.lumn_red);
        lumngreen = (TextView)findViewById(R.id.lumn_green);
        lumnblue = (TextView)findViewById(R.id.lumn_blue);
        l = (TextView)findViewById(R.id.l);
        r = (TextView)findViewById(R.id.r);
        g = (TextView)findViewById(R.id.g);
        b = (TextView)findViewById(R.id.b);
        c1 = (ImageButton)findViewById(R.id.imageButton2);
        c2 = (ImageButton)findViewById(R.id.imageButton3);
        c3 = (ImageButton)findViewById(R.id.imageButton4);
        c4 = (ImageButton)findViewById(R.id.imageButton5);
        c5 = (ImageButton)findViewById(R.id.imageButton6);
        c6 = (ImageButton)findViewById(R.id.imageButton7);
        c7 = (ImageButton)findViewById(R.id.imageButton8);
        ringnumber = (SeekBar)findViewById(R.id.seekBar5);

        new ConnectBT().execute(); //Call the class to connect

        //commands to be sent to bluetooth

        //Button - TURN OFF
        btnOff.setOnClickListener(new OnClickListener() {
            @Override
            public void onClick(View v)
            {
                turnOffLed();
            }
        });

        //Button - Sequence1
        btnS1.setOnClickListener(new OnClickListener(){
        public void onClick(View v)
        {
            if (Socket!=null)
            {
                try
                {
                    if(btnS1.getCurrentTextColor()==Color.RED)
                    {
                        Toast.makeText(getApplicationContext(),"SEQUENCE IS ON", Toast.LENGTH_SHORT).show();
                    }
                    else
                    if(btnS2.getCurrentTextColor()==Color.RED || btnS3.getCurrentTextColor()==Color.RED || btnS4.getCurrentTextColor()==Color.RED||btnS5.getCurrentTextColor()==Color.RED||btnS6.getCurrentTextColor()==Color.RED)
                    {
                        Toast.makeText(getApplicationContext(),"TURN OFF THE OTHER SEQUENCE", Toast.LENGTH_SHORT).show();
                    }
                    else
                    {
                        if(temp_ring==0) //ring1
                        {
                            {
                                Socket.getOutputStream().write('R');
                                Socket.getOutputStream().write(Integer.valueOf(0));
                                Socket.getOutputStream().write('G');
                                Socket.getOutputStream().write(Integer.valueOf(0));
                                Socket.getOutputStream().write('B');
                                Socket.getOutputStream().write(Integer.valueOf(0));
                                red.setProgress(0);
                                green.setProgress(0);
                                blue.setProgress(0);
                                brightness.setProgress(10);
                                Integer pr = 0;
                                lumnred.setText(String.valueOf(progress));
                                r.setText(String.valueOf(pr));
                                lumngreen.setText(String.valueOf(progress));
                                g.setText(String.valueOf(pr));
                                lumnblue.setText(String.valueOf(progress));
                                b.setText(String.valueOf(pr));
                                l.setText(String.valueOf(100+"%"));
                                pr_redR1 = 0;
                                pr_greenR1 = 0;
                                pr_blueR1 = 0;
                                pr_brightnessR1 = 10;
                                temp_S1R1 = 1;
                                temp_S2R1 = 0;
                                temp_S3R1 = 0;
                                temp_S4R1 = 0;
                                temp_S5R1 = 0;
                                temp_S6R1 = 0;
                                btnS1.setTextColor(Color.RED);
                                btnS1.setTextSize(22);
                                Socket.getOutputStream().write('a');
                            }
                        }
                        if(temp_ring==1) //ring2
                        {
                            {
                                Socket.getOutputStream().write('R');
                                Socket.getOutputStream().write(Integer.valueOf(0));
                                Socket.getOutputStream().write('G');
                                Socket.getOutputStream().write(Integer.valueOf(0));
                                Socket.getOutputStream().write('B');
                                Socket.getOutputStream().write(Integer.valueOf(0));
                                red.setProgress(0);
                                green.setProgress(0);
                                blue.setProgress(0);
                                brightness.setProgress(10);
                                Integer pr = 0;
                                lumnred.setText(String.valueOf(progress));
                                r.setText(String.valueOf(pr));
                                lumngreen.setText(String.valueOf(progress));
                                g.setText(String.valueOf(pr));
                                lumnblue.setText(String.valueOf(progress));
                                b.setText(String.valueOf(pr));
                                l.setText(String.valueOf(100+"%"));
                                pr_redR2 = 0;
                                pr_greenR2 = 0;
                                pr_blueR2 = 0;
                                pr_brightnessR2 = 10;
                                temp_S1R2 = 1;
                                temp_S2R2 = 0;
                                temp_S3R2 = 0;
                                temp_S4R2 = 0;
                                temp_S5R2 = 0;
                                temp_S6R2 = 0;
                                btnS1.setTextColor(Color.RED);
                                btnS1.setTextSize(22);
                                Socket.getOutputStream().write('a');
                            }
                        }
                    }
                }
                catch (IOException e)
                {
                    msg("Error");
                }
            }
        }
        });

        //Button - Sequence2
        btnS2.setOnClickListener(new OnClickListener(){
            public void onClick(View v)
            {
                if (Socket!=null)
                {
                    try
                    {
                        if(btnS2.getCurrentTextColor()==Color.RED)
                        {
                            Toast.makeText(getApplicationContext(),"SEQUENCE IS ON", Toast.LENGTH_SHORT).show();
                        }
                        else
                        if(btnS1.getCurrentTextColor()==Color.RED || btnS3.getCurrentTextColor()==Color.RED ||btnS4.getCurrentTextColor()==Color.RED||btnS5.getCurrentTextColor()==Color.RED||btnS6.getCurrentTextColor()==Color.RED)
                        {
                            Toast.makeText(getApplicationContext(),"TURN OFF THE OTHER SEQUENCE", Toast.LENGTH_SHORT).show();
                        }
                        else
                        {
                            if(temp_ring==0) //ring1
                            {
                                {
                                    Socket.getOutputStream().write('R');
                                    Socket.getOutputStream().write(Integer.valueOf(0));
                                    Socket.getOutputStream().write('G');
                                    Socket.getOutputStream().write(Integer.valueOf(0));
                                    Socket.getOutputStream().write('B');
                                    Socket.getOutputStream().write(Integer.valueOf(0));
                                    red.setProgress(0);
                                    green.setProgress(0);
                                    blue.setProgress(0);
                                    brightness.setProgress(10);
                                    Integer pr = 0;
                                    lumnred.setText(String.valueOf(progress));
                                    r.setText(String.valueOf(pr));
                                    lumngreen.setText(String.valueOf(progress));
                                    g.setText(String.valueOf(pr));
                                    lumnblue.setText(String.valueOf(progress));
                                    b.setText(String.valueOf(pr));
                                    l.setText(String.valueOf(100+"%"));
                                    pr_redR1 = 0;
                                    pr_greenR1 = 0;
                                    pr_blueR1 = 0;
                                    pr_brightnessR1 = 10;
                                    temp_S1R1 = 0;
                                    temp_S2R1 = 1;
                                    temp_S3R1 = 0;
                                    temp_S4R1 = 0;
                                    temp_S5R1 = 0;
                                    temp_S6R1 = 0;
                                    btnS2.setTextColor(Color.RED);
                                    btnS2.setTextSize(22);
                                    Socket.getOutputStream().write('b');
                                }
                            }
                            if(temp_ring==1) //ring2
                            {
                                {
                                    Socket.getOutputStream().write('R');
                                    Socket.getOutputStream().write(Integer.valueOf(0));
                                    Socket.getOutputStream().write('G');
                                    Socket.getOutputStream().write(Integer.valueOf(0));
                                    Socket.getOutputStream().write('B');
                                    Socket.getOutputStream().write(Integer.valueOf(0));
                                    red.setProgress(0);
                                    green.setProgress(0);
                                    blue.setProgress(0);
                                    brightness.setProgress(10);
                                    Integer pr = 0;
                                    lumnred.setText(String.valueOf(progress));
                                    r.setText(String.valueOf(pr));
                                    lumngreen.setText(String.valueOf(progress));
                                    g.setText(String.valueOf(pr));
                                    lumnblue.setText(String.valueOf(progress));
                                    b.setText(String.valueOf(pr));
                                    l.setText(String.valueOf(100+"%"));
                                    pr_redR2 = 0;
                                    pr_greenR2 = 0;
                                    pr_blueR2 = 0;
                                    pr_brightnessR2 = 10;
                                    temp_S1R2 = 0;
                                    temp_S2R2 = 1;
                                    temp_S3R2 = 0;
                                    temp_S4R2 = 0;
                                    temp_S5R2 = 0;
                                    temp_S6R2 = 0;
                                    btnS2.setTextColor(Color.RED);
                                    btnS2.setTextSize(22);
                                    Socket.getOutputStream().write('b');
                                }
                            }
                        }
                    }
                    catch (IOException e)
                    {
                        msg("Error");
                    }
                }
            }
        });

        //Button - Sequence3
        btnS3.setOnClickListener(new OnClickListener(){
            public void onClick(View v)
            {
                if (Socket!=null)
                {
                    try
                    {
                        if(btnS3.getCurrentTextColor()==Color.RED)
                        {
                            Toast.makeText(getApplicationContext(),"SEQUENCE IS ON", Toast.LENGTH_SHORT).show();
                        }
                        else
                        if(btnS1.getCurrentTextColor()==Color.RED || btnS2.getCurrentTextColor()==Color.RED ||btnS4.getCurrentTextColor()==Color.RED||btnS5.getCurrentTextColor()==Color.RED||btnS6.getCurrentTextColor()==Color.RED)
                        {
                            Toast.makeText(getApplicationContext(),"TURN OFF THE OTHER SEQUENCE", Toast.LENGTH_SHORT).show();
                        }
                        else
                        {
                            if(temp_ring==0) //ring1
                            {
                                {
                                    Socket.getOutputStream().write('R');
                                    Socket.getOutputStream().write(Integer.valueOf(0));
                                    Socket.getOutputStream().write('G');
                                    Socket.getOutputStream().write(Integer.valueOf(0));
                                    Socket.getOutputStream().write('B');
                                    Socket.getOutputStream().write(Integer.valueOf(0));
                                    red.setProgress(0);
                                    green.setProgress(0);
                                    blue.setProgress(0);
                                    brightness.setProgress(10);
                                    Integer pr = 0;
                                    lumnred.setText(String.valueOf(progress));
                                    r.setText(String.valueOf(pr));
                                    lumngreen.setText(String.valueOf(progress));
                                    g.setText(String.valueOf(pr));
                                    lumnblue.setText(String.valueOf(progress));
                                    b.setText(String.valueOf(pr));
                                    l.setText(String.valueOf(100+"%"));
                                    pr_redR1 = 0;
                                    pr_greenR1 = 0;
                                    pr_blueR1 = 0;
                                    pr_brightnessR1 = 10;
                                    temp_S1R1 = 0;
                                    temp_S2R1 = 0;
                                    temp_S3R1 = 1;
                                    temp_S4R1 = 0;
                                    temp_S5R1 = 0;
                                    temp_S6R1 = 0;
                                    btnS3.setTextColor(Color.RED);
                                    btnS3.setTextSize(22);
                                    Socket.getOutputStream().write('c');
                                }
                            }
                            if(temp_ring==1) //ring2
                            {
                                {
                                    Socket.getOutputStream().write('R');
                                    Socket.getOutputStream().write(Integer.valueOf(0));
                                    Socket.getOutputStream().write('G');
                                    Socket.getOutputStream().write(Integer.valueOf(0));
                                    Socket.getOutputStream().write('B');
                                    Socket.getOutputStream().write(Integer.valueOf(0));
                                    red.setProgress(0);
                                    green.setProgress(0);
                                    blue.setProgress(0);
                                    brightness.setProgress(10);
                                    Integer pr = 0;
                                    lumnred.setText(String.valueOf(progress));
                                    r.setText(String.valueOf(pr));
                                    lumngreen.setText(String.valueOf(progress));
                                    g.setText(String.valueOf(pr));
                                    lumnblue.setText(String.valueOf(progress));
                                    b.setText(String.valueOf(pr));
                                    l.setText(String.valueOf(100+"%"));
                                    pr_redR2 = 0;
                                    pr_greenR2 = 0;
                                    pr_blueR2 = 0;
                                    pr_brightnessR2 = 10;
                                    temp_S1R2 = 0;
                                    temp_S2R2 = 0;
                                    temp_S3R2 = 1;
                                    temp_S4R2 = 0;
                                    temp_S5R2 = 0;
                                    temp_S6R2 = 0;
                                    btnS3.setTextColor(Color.RED);
                                    btnS3.setTextSize(22);
                                    Socket.getOutputStream().write('c');
                                }
                            }
                        }
                    }
                    catch (IOException e)
                    {
                        msg("Error");
                    }
                }
            }
        });

        //Button - Sequence4
        btnS4.setOnClickListener(new OnClickListener(){
            public void onClick(View v)
            {
                if (Socket!=null)
                {
                    try
                    {
                        if(btnS4.getCurrentTextColor()==Color.RED)
                        {
                            Toast.makeText(getApplicationContext(),"SEQUENCE IS ON", Toast.LENGTH_SHORT).show();
                        }
                        else
                        if(btnS1.getCurrentTextColor()==Color.RED || btnS2.getCurrentTextColor()==Color.RED ||btnS3.getCurrentTextColor()==Color.RED||btnS5.getCurrentTextColor()==Color.RED||btnS6.getCurrentTextColor()==Color.RED)
                        {
                            Toast.makeText(getApplicationContext(),"TURN OFF THE OTHER SEQUENCE", Toast.LENGTH_SHORT).show();
                        }
                        else
                        {
                            if(temp_ring==0) //ring1
                            {
                                {
                                    Socket.getOutputStream().write('R');
                                    Socket.getOutputStream().write(Integer.valueOf(0));
                                    Socket.getOutputStream().write('G');
                                    Socket.getOutputStream().write(Integer.valueOf(0));
                                    Socket.getOutputStream().write('B');
                                    Socket.getOutputStream().write(Integer.valueOf(0));
                                    red.setProgress(0);
                                    green.setProgress(0);
                                    blue.setProgress(0);
                                    brightness.setProgress(10);
                                    Integer pr = 0;
                                    lumnred.setText(String.valueOf(progress));
                                    r.setText(String.valueOf(pr));
                                    lumngreen.setText(String.valueOf(progress));
                                    g.setText(String.valueOf(pr));
                                    lumnblue.setText(String.valueOf(progress));
                                    b.setText(String.valueOf(pr));
                                    l.setText(String.valueOf(100+"%"));
                                    pr_redR1 = 0;
                                    pr_greenR1 = 0;
                                    pr_blueR1 = 0;
                                    pr_brightnessR1 = 10;
                                    temp_S1R1 = 0;
                                    temp_S2R1 = 0;
                                    temp_S3R1 = 0;
                                    temp_S4R1 = 1;
                                    temp_S5R1 = 0;
                                    temp_S6R1 = 0;
                                    btnS4.setTextColor(Color.RED);
                                    btnS4.setTextSize(22);
                                    Socket.getOutputStream().write('d');
                                }
                            }
                            if(temp_ring==1) //ring2
                            {
                                {
                                    Socket.getOutputStream().write('R');
                                    Socket.getOutputStream().write(Integer.valueOf(0));
                                    Socket.getOutputStream().write('G');
                                    Socket.getOutputStream().write(Integer.valueOf(0));
                                    Socket.getOutputStream().write('B');
                                    Socket.getOutputStream().write(Integer.valueOf(0));
                                    red.setProgress(0);
                                    green.setProgress(0);
                                    blue.setProgress(0);
                                    brightness.setProgress(10);
                                    Integer pr = 0;
                                    lumnred.setText(String.valueOf(progress));
                                    r.setText(String.valueOf(pr));
                                    lumngreen.setText(String.valueOf(progress));
                                    g.setText(String.valueOf(pr));
                                    lumnblue.setText(String.valueOf(progress));
                                    b.setText(String.valueOf(pr));
                                    l.setText(String.valueOf(100+"%"));
                                    pr_redR2 = 0;
                                    pr_greenR2 = 0;
                                    pr_blueR2 = 0;
                                    pr_brightnessR2 = 10;
                                    temp_S1R2 = 0;
                                    temp_S2R2 = 0;
                                    temp_S3R2 = 0;
                                    temp_S4R2 = 1;
                                    temp_S5R2 = 0;
                                    temp_S6R2 = 0;
                                    btnS4.setTextColor(Color.RED);
                                    btnS4.setTextSize(22);
                                    Socket.getOutputStream().write('d');
                                }
                            }
                        }
                    }
                    catch (IOException e)
                    {
                        msg("Error");
                    }
                }
            }
        });

        //Button - Sequence5
        btnS5.setOnClickListener(new OnClickListener(){
            public void onClick(View v)
            {
                if (Socket!=null)
                {
                    try
                    {
                        if(btnS5.getCurrentTextColor()==Color.RED)
                        {
                            Toast.makeText(getApplicationContext(),"SEQUENCE IS ON", Toast.LENGTH_SHORT).show();
                        }
                        else
                        if(btnS1.getCurrentTextColor()==Color.RED || btnS2.getCurrentTextColor()==Color.RED ||btnS3.getCurrentTextColor()==Color.RED||btnS4.getCurrentTextColor()==Color.RED||btnS6.getCurrentTextColor()==Color.RED)
                        {
                            Toast.makeText(getApplicationContext(),"TURN OFF THE OTHER SEQUENCE", Toast.LENGTH_SHORT).show();
                        }
                        else
                        {
                            if(temp_ring==0) //ring1
                            {
                                {
                                    Socket.getOutputStream().write('R');
                                    Socket.getOutputStream().write(Integer.valueOf(0));
                                    Socket.getOutputStream().write('G');
                                    Socket.getOutputStream().write(Integer.valueOf(0));
                                    Socket.getOutputStream().write('B');
                                    Socket.getOutputStream().write(Integer.valueOf(0));
                                    red.setProgress(0);
                                    green.setProgress(0);
                                    blue.setProgress(0);
                                    brightness.setProgress(10);
                                    Integer pr = 0;
                                    lumnred.setText(String.valueOf(progress));
                                    r.setText(String.valueOf(pr));
                                    lumngreen.setText(String.valueOf(progress));
                                    g.setText(String.valueOf(pr));
                                    lumnblue.setText(String.valueOf(progress));
                                    b.setText(String.valueOf(pr));
                                    l.setText(String.valueOf(100+"%"));
                                    pr_redR1 = 0;
                                    pr_greenR1 = 0;
                                    pr_blueR1 = 0;
                                    pr_brightnessR1 = 10;
                                    temp_S1R1 = 0;
                                    temp_S2R1 = 0;
                                    temp_S3R1 = 0;
                                    temp_S4R1 = 0;
                                    temp_S5R1 = 1;
                                    temp_S6R1 = 0;
                                    btnS5.setTextColor(Color.RED);
                                    btnS5.setTextSize(22);
                                    Socket.getOutputStream().write('e');
                                }
                            }
                            if(temp_ring==1) //ring2
                            {
                                {
                                    Socket.getOutputStream().write('R');
                                    Socket.getOutputStream().write(Integer.valueOf(0));
                                    Socket.getOutputStream().write('G');
                                    Socket.getOutputStream().write(Integer.valueOf(0));
                                    Socket.getOutputStream().write('B');
                                    Socket.getOutputStream().write(Integer.valueOf(0));
                                    red.setProgress(0);
                                    green.setProgress(0);
                                    blue.setProgress(0);
                                    brightness.setProgress(10);
                                    Integer pr = 0;
                                    lumnred.setText(String.valueOf(progress));
                                    r.setText(String.valueOf(pr));
                                    lumngreen.setText(String.valueOf(progress));
                                    g.setText(String.valueOf(pr));
                                    lumnblue.setText(String.valueOf(progress));
                                    b.setText(String.valueOf(pr));
                                    l.setText(String.valueOf(100+"%"));
                                    pr_redR2 = 0;
                                    pr_greenR2 = 0;
                                    pr_blueR2 = 0;
                                    pr_brightnessR2 = 10;
                                    temp_S1R2 = 0;
                                    temp_S2R2 = 0;
                                    temp_S3R2 = 0;
                                    temp_S4R2 = 0;
                                    temp_S5R2 = 1;
                                    temp_S6R2 = 0;
                                    btnS5.setTextColor(Color.RED);
                                    btnS5.setTextSize(22);
                                    Socket.getOutputStream().write('e');
                                }
                            }
                        }
                    }
                    catch (IOException e)
                    {
                        msg("Error");
                    }
                }
            }
        });

        //Button - Sequence6
        btnS6.setOnClickListener(new OnClickListener(){
            public void onClick(View v)
            {
                if (Socket!=null)
                {
                    try
                    {
                        if(btnS6.getCurrentTextColor()==Color.RED)
                        {
                            Toast.makeText(getApplicationContext(),"SEQUENCE IS ON", Toast.LENGTH_SHORT).show();
                        }
                        else
                        if(btnS1.getCurrentTextColor()==Color.RED || btnS2.getCurrentTextColor()==Color.RED ||btnS3.getCurrentTextColor()==Color.RED||btnS4.getCurrentTextColor()==Color.RED||btnS5.getCurrentTextColor()==Color.RED)
                        {
                            Toast.makeText(getApplicationContext(),"TURN OFF THE OTHER SEQUENCE", Toast.LENGTH_SHORT).show();
                        }
                        else
                        {
                            if(temp_ring==0) //ring1
                            {
                                {
                                    Socket.getOutputStream().write('R');
                                    Socket.getOutputStream().write(Integer.valueOf(0));
                                    Socket.getOutputStream().write('G');
                                    Socket.getOutputStream().write(Integer.valueOf(0));
                                    Socket.getOutputStream().write('B');
                                    Socket.getOutputStream().write(Integer.valueOf(0));
                                    red.setProgress(0);
                                    green.setProgress(0);
                                    blue.setProgress(0);
                                    brightness.setProgress(10);
                                    Integer pr = 0;
                                    lumnred.setText(String.valueOf(progress));
                                    r.setText(String.valueOf(pr));
                                    lumngreen.setText(String.valueOf(progress));
                                    g.setText(String.valueOf(pr));
                                    lumnblue.setText(String.valueOf(progress));
                                    b.setText(String.valueOf(pr));
                                    l.setText(String.valueOf(100+"%"));
                                    pr_redR1 = 0;
                                    pr_greenR1 = 0;
                                    pr_blueR1 = 0;
                                    pr_brightnessR1 = 10;
                                    temp_S1R1 = 0;
                                    temp_S2R1 = 0;
                                    temp_S3R1 = 0;
                                    temp_S4R1 = 0;
                                    temp_S5R1 = 0;
                                    temp_S6R1 = 1;
                                    btnS6.setTextColor(Color.RED);
                                    btnS6.setTextSize(22);
                                    Socket.getOutputStream().write('f');
                                }
                            }
                            if(temp_ring==1) //ring2
                            {
                                {
                                    Socket.getOutputStream().write('R');
                                    Socket.getOutputStream().write(Integer.valueOf(0));
                                    Socket.getOutputStream().write('G');
                                    Socket.getOutputStream().write(Integer.valueOf(0));
                                    Socket.getOutputStream().write('B');
                                    Socket.getOutputStream().write(Integer.valueOf(0));
                                    red.setProgress(0);
                                    green.setProgress(0);
                                    blue.setProgress(0);
                                    brightness.setProgress(10);
                                    Integer pr = 0;
                                    lumnred.setText(String.valueOf(progress));
                                    r.setText(String.valueOf(pr));
                                    lumngreen.setText(String.valueOf(progress));
                                    g.setText(String.valueOf(pr));
                                    lumnblue.setText(String.valueOf(progress));
                                    b.setText(String.valueOf(pr));
                                    l.setText(String.valueOf(100+"%"));
                                    pr_redR2 = 0;
                                    pr_greenR2 = 0;
                                    pr_blueR2 = 0;
                                    pr_brightnessR2 = 10;
                                    temp_S1R2 = 0;
                                    temp_S2R2 = 0;
                                    temp_S3R2 = 0;
                                    temp_S4R2 = 0;
                                    temp_S5R2 = 0;
                                    temp_S6R2 = 1;
                                    btnS6.setTextColor(Color.RED);
                                    btnS6.setTextSize(22);
                                    Socket.getOutputStream().write('f');
                                }
                            }
                        }
                    }
                    catch (IOException e)
                    {
                        msg("Error");
                    }
                }
            }
        });

        //Button - Disconnected (return to the first layout - PairDevice)
        btnDis.setOnClickListener(new OnClickListener()
        {
            @Override
            public void onClick(View v)
            {
                Disconnect();
            }
        });

        //SeekBar - Brightness
        brightness.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            @Override
            public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
                if (fromUser==true)
                {
                    if(btnS1.getCurrentTextColor()==Color.RED || btnS2.getCurrentTextColor()==Color.RED ||btnS3.getCurrentTextColor()==Color.RED||btnS4.getCurrentTextColor()==Color.RED||btnS5.getCurrentTextColor()==Color.RED||btnS6.getCurrentTextColor()==Color.RED)
                    {
                        brightness.setProgress(10);
                    }
                    else
                    {
                        lumn.setText(String.valueOf(progress));
                        Integer pr = progress * 10;

                        if (temp_ring == 0) //ring1
                        {
                            pr_brightnessR1 = progress;
                        }
                        if (temp_ring == 1) //ring2
                        {
                            pr_brightnessR2 = progress;
                        }
                        l.setText(String.valueOf(pr) + "%");

                        try {
                            Socket.getOutputStream().write('L');

                            Socket.getOutputStream().write(Integer.valueOf(progress));
                        }
                        catch (IOException e)
                        {
                            msg("Error");
                        }
                    }
                }
            }
            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {

            }
            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {

            }
        });

        //SeekBar - Red Color
        red.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            @Override
            public void onProgressChanged(SeekBar seekBar2, int progress, boolean fromUser) {
                if (fromUser==true)
                {
                    if(btnS1.getCurrentTextColor()==Color.RED || btnS2.getCurrentTextColor()==Color.RED ||btnS3.getCurrentTextColor()==Color.RED||btnS4.getCurrentTextColor()==Color.RED||btnS5.getCurrentTextColor()==Color.RED||btnS6.getCurrentTextColor()==Color.RED)
                    {
                        red.setProgress(0);
                    }
                    else
                    {
                        lumnred.setText(String.valueOf(progress));
                        Integer pr = progress * 4 - 1;

                        if (temp_ring == 0)
                        {
                            pr_redR1 = progress;
                        }
                        if (temp_ring == 1)
                        {
                            pr_redR2 = progress;
                        }
                        if (pr == -1) {
                            pr = pr + 1;
                        }
                        r.setText(String.valueOf(pr));
                        try
                        {
                            Socket.getOutputStream().write('R');
                            Socket.getOutputStream().write(Integer.valueOf(progress));
                        }
                        catch (IOException e)
                        {
                            msg("Error");
                        }
                    }
                }
            }
            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {

            }
            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {

            }
        });

        //SeekBar - Green Color
        green.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            @Override
            public void onProgressChanged(SeekBar seekBar3, int progress, boolean fromUser) {
                if (fromUser==true)
                {
                    if(btnS1.getCurrentTextColor()==Color.RED || btnS2.getCurrentTextColor()==Color.RED ||btnS3.getCurrentTextColor()==Color.RED||btnS4.getCurrentTextColor()==Color.RED||btnS5.getCurrentTextColor()==Color.RED||btnS6.getCurrentTextColor()==Color.RED)
                    {
                        green.setProgress(0);
                    }
                    else
                    {
                        lumngreen.setText(String.valueOf(progress));
                        Integer pr = progress * 4 - 1;

                        if (temp_ring == 0)
                        {
                            pr_greenR1 = progress;
                        }
                        if (temp_ring == 1)
                        {
                            pr_greenR2 = progress;
                        }
                        if (pr == -1)
                        {
                            pr = pr + 1;
                        }
                        g.setText(String.valueOf(pr));
                        try
                        {
                            Socket.getOutputStream().write('G');
                            Socket.getOutputStream().write(Integer.valueOf(progress));
                        }
                        catch (IOException e)
                        {
                            msg("Error");
                        }
                    }
                }
            }
            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {

            }
            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {

            }
        });

        //SeekBar - Blue Color
        blue.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            @Override
            public void onProgressChanged(SeekBar seekBar4, int progress, boolean fromUser) {
                if (fromUser==true)
                {
                    if(btnS1.getCurrentTextColor()==Color.RED || btnS2.getCurrentTextColor()==Color.RED ||btnS3.getCurrentTextColor()==Color.RED||btnS4.getCurrentTextColor()==Color.RED||btnS5.getCurrentTextColor()==Color.RED||btnS6.getCurrentTextColor()==Color.RED)
                    {
                        blue.setProgress(0);
                    }
                    else
                    {
                        lumnblue.setText(String.valueOf(progress));
                        Integer pr = progress * 4 - 1;

                        if (temp_ring == 0)
                        {
                            pr_blueR1 = progress;
                        }
                        if (temp_ring == 1)
                        {
                            pr_blueR2 = progress;
                        }
                        if (pr == -1)
                        {
                            pr = pr + 1;
                        }
                        b.setText(String.valueOf(pr));
                        try
                        {
                            Socket.getOutputStream().write('B');
                            Socket.getOutputStream().write(Integer.valueOf(progress));
                        }
                        catch (IOException e)
                        {
                            msg("Error");
                        }
                    }
                }
            }
            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {

            }
            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {

            }
        });

        //Button - Color1
        c1.setOnClickListener(new OnClickListener(){
            public void onClick(View v)
            {
                if (Socket!=null)
                {
                    if(btnS1.getCurrentTextColor()==Color.RED || btnS2.getCurrentTextColor()==Color.RED ||btnS3.getCurrentTextColor()==Color.RED||btnS4.getCurrentTextColor()==Color.RED||btnS5.getCurrentTextColor()==Color.RED||btnS6.getCurrentTextColor()==Color.RED)
                    {
                        Toast.makeText(getApplicationContext(),"TURN OFF THE SEQUENCE", Toast.LENGTH_SHORT).show();
                    }
                    else
                    {
                        try
                        {
                            if (temp_ring == 0)
                            {
                                pr_redR1 = 34;
                            }
                            if (temp_ring == 1)
                            {
                                pr_redR2 = 34;
                            }
                            if (temp_ring == 0)
                            {
                                pr_greenR1 = 8;
                            }
                            if (temp_ring == 1)
                            {
                                pr_greenR2 = 8;
                            }
                            if (temp_ring == 0)
                            {
                                pr_blueR1 = 0;
                            }
                            if (temp_ring == 1)
                            {
                                pr_blueR2 = 0;
                            }
                            red.setProgress(34);
                            green.setProgress(8);
                            blue.setProgress(0);
                            Integer red = 135;
                            Integer green = 31;
                            Integer blue = 0;
                            lumnred.setText(String.valueOf(progress));
                            r.setText(String.valueOf(red));
                            lumngreen.setText(String.valueOf(progress));
                            g.setText(String.valueOf(green));
                            lumnblue.setText(String.valueOf(progress));
                            b.setText(String.valueOf(blue));
                            Socket.getOutputStream().write('g');
                        }
                        catch (IOException e)
                        {
                            msg("Error");
                        }
                    }
                }
            }
        });

        //Button - Color2
        c2.setOnClickListener(new OnClickListener(){
            public void onClick(View v)
            {
                if (Socket!=null)
                {
                    if(btnS1.getCurrentTextColor()==Color.RED || btnS2.getCurrentTextColor()==Color.RED ||btnS3.getCurrentTextColor()==Color.RED||btnS4.getCurrentTextColor()==Color.RED||btnS5.getCurrentTextColor()==Color.RED||btnS6.getCurrentTextColor()==Color.RED)
                    {
                        Toast.makeText(getApplicationContext(),"TURN OFF SEQUENCE", Toast.LENGTH_SHORT).show();
                    }
                    else
                        {
                        try
                        {
                            if (temp_ring == 0)
                            {
                                pr_redR1 = 49;
                            }
                            if (temp_ring == 1)
                            {
                                pr_redR2 = 49;
                            }
                            if (temp_ring == 0)
                            {
                                pr_greenR1 = 3;
                            }
                            if (temp_ring == 1)
                            {
                                pr_greenR2 = 3;
                            }
                            if (temp_ring == 0)
                            {
                                pr_blueR1 = 0;
                            }
                            if (temp_ring == 1)
                            {
                                pr_blueR2 = 0;
                            }
                            red.setProgress(49);
                            green.setProgress(3);
                            blue.setProgress(0);
                            Integer red = 195;
                            Integer green = 111;
                            Integer blue = 0;
                            lumnred.setText(String.valueOf(progress));
                            r.setText(String.valueOf(red));
                            lumngreen.setText(String.valueOf(progress));
                            g.setText(String.valueOf(green));
                            lumnblue.setText(String.valueOf(progress));
                            b.setText(String.valueOf(blue));
                            Socket.getOutputStream().write('h');
                        }
                        catch (IOException e)
                        {
                            msg("Error");
                        }
                    }
                }
            }
        });

        //Button - Color3
        c3.setOnClickListener(new OnClickListener(){
            public void onClick(View v)
            {
                if (Socket!=null)
                {
                    if(btnS1.getCurrentTextColor()==Color.RED || btnS2.getCurrentTextColor()==Color.RED ||btnS3.getCurrentTextColor()==Color.RED||btnS4.getCurrentTextColor()==Color.RED||btnS5.getCurrentTextColor()==Color.RED||btnS6.getCurrentTextColor()==Color.RED)
                    {
                        Toast.makeText(getApplicationContext(),"TURN OFF THE SEQUENCE", Toast.LENGTH_SHORT).show();
                    }
                    else
                    {
                        try
                        {
                            if (temp_ring == 0)
                            {
                                pr_redR1 = 6;
                            }
                            if (temp_ring == 1)
                            {
                                pr_redR2 = 6;
                            }
                            if (temp_ring == 0)
                            {
                                pr_greenR1 = 25;
                            }
                            if (temp_ring == 1)
                            {
                                pr_greenR2 = 25;
                            }
                            if (temp_ring == 0)
                            {
                                pr_blueR1 = 0;
                            }
                            if (temp_ring == 1)
                            {
                                pr_blueR2 = 0;
                            }
                            red.setProgress(6);
                            green.setProgress(25);
                            blue.setProgress(0);
                            Integer red = 24;
                            Integer green = 100;
                            Integer blue = 0;
                            lumnred.setText(String.valueOf(progress));
                            r.setText(String.valueOf(red));
                            lumngreen.setText(String.valueOf(progress));
                            g.setText(String.valueOf(green));
                            lumnblue.setText(String.valueOf(progress));
                            b.setText(String.valueOf(blue));
                            Socket.getOutputStream().write('i');
                        }
                        catch (IOException e)
                        {
                            msg("Error");
                        }
                    }
                }
            }
        });

        //Button - Color4
        c4.setOnClickListener(new OnClickListener(){
            public void onClick(View v)
            {
                if (Socket!=null)
                {
                    if(btnS1.getCurrentTextColor()==Color.RED || btnS2.getCurrentTextColor()==Color.RED ||btnS3.getCurrentTextColor()==Color.RED||btnS4.getCurrentTextColor()==Color.RED||btnS5.getCurrentTextColor()==Color.RED||btnS6.getCurrentTextColor()==Color.RED)
                    {
                        Toast.makeText(getApplicationContext(),"TURN OFF THE SEQUENCE", Toast.LENGTH_SHORT).show();
                    }
                    else
                        {
                        try
                        {
                            if (temp_ring == 0)
                            {
                                pr_redR1 = 0;
                            }
                            if (temp_ring == 1)
                            {
                                pr_redR2 = 0;
                            }
                            if (temp_ring == 0)
                            {
                                pr_greenR1 = 61;
                            }
                            if (temp_ring == 1)
                            {
                                pr_greenR2 = 61;
                            }
                            if (temp_ring == 0)
                            {
                                pr_blueR1 = 19;
                            }
                            if (temp_ring == 1)
                            {
                                pr_blueR2 = 19;
                            }
                            red.setProgress(0);
                            green.setProgress(61);
                            blue.setProgress(19);
                            Integer red = 0;
                            Integer green = 243;
                            Integer blue = 75;
                            lumnred.setText(String.valueOf(progress));
                            r.setText(String.valueOf(red));
                            lumngreen.setText(String.valueOf(progress));
                            g.setText(String.valueOf(green));
                            lumnblue.setText(String.valueOf(progress));
                            b.setText(String.valueOf(blue));
                            Socket.getOutputStream().write('j');
                        }
                        catch (IOException e)
                        {
                            msg("Error");
                        }
                    }
                }
            }
        });

        //Button - Color5
        c5.setOnClickListener(new OnClickListener(){
            public void onClick(View v)
            {
                if (Socket!=null)
                {
                    if(btnS1.getCurrentTextColor()==Color.RED || btnS2.getCurrentTextColor()==Color.RED ||btnS3.getCurrentTextColor()==Color.RED||btnS4.getCurrentTextColor()==Color.RED||btnS5.getCurrentTextColor()==Color.RED||btnS6.getCurrentTextColor()==Color.RED)
                    {
                        Toast.makeText(getApplicationContext(),"TURN OFF THE SEQUENCE", Toast.LENGTH_SHORT).show();
                    }
                    else
                        {
                        try
                        {
                            if (temp_ring == 0)
                            {
                                pr_redR1 = 64;
                            }
                            if (temp_ring == 1)
                            {
                                pr_redR2 = 64;
                            }
                            if (temp_ring == 0)
                            {
                                pr_greenR1 = 0;
                            }
                            if (temp_ring == 1)
                            {
                                pr_greenR2 = 0;
                            }
                            if (temp_ring == 0)
                            {
                                pr_blueR1 = 13;
                            }
                            if (temp_ring == 1)
                            {
                                pr_blueR2 = 13;
                            }
                            red.setProgress(64);
                            green.setProgress(0);
                            blue.setProgress(13);
                            Integer red = 255;
                            Integer green = 0;
                            Integer blue = 51;
                            lumnred.setText(String.valueOf(progress));
                            r.setText(String.valueOf(red));
                            lumngreen.setText(String.valueOf(progress));
                            g.setText(String.valueOf(green));
                            lumnblue.setText(String.valueOf(progress));
                            b.setText(String.valueOf(blue));
                            Socket.getOutputStream().write('k');
                        }
                        catch (IOException e)
                        {
                            msg("Error");
                        }
                    }
                }
            }
        });

        //Button - Color6
        c6.setOnClickListener(new OnClickListener(){
            public void onClick(View v)
            {
                if (Socket!=null)
                {
                    if(btnS1.getCurrentTextColor()==Color.RED || btnS2.getCurrentTextColor()==Color.RED ||btnS3.getCurrentTextColor()==Color.RED||btnS4.getCurrentTextColor()==Color.RED||btnS5.getCurrentTextColor()==Color.RED||btnS6.getCurrentTextColor()==Color.RED)
                    {
                        Toast.makeText(getApplicationContext(),"TURN OFF THE SEQUENCE", Toast.LENGTH_SHORT).show();
                    }
                    else
                        {
                        try
                        {
                            if (temp_ring == 0)
                            {
                                pr_redR1 = 64;
                            }
                            if (temp_ring == 1)
                            {
                                pr_redR2 = 64;
                            }
                            if (temp_ring == 0)
                            {
                                pr_greenR1 = 0;
                            }
                            if (temp_ring == 1)
                            {
                                pr_greenR2 = 0;
                            }
                            if (temp_ring == 0)
                            {
                                pr_blueR1 = 64;
                            }
                            if (temp_ring == 1)
                            {
                                pr_blueR2 = 64;
                            }
                            red.setProgress(64);
                            green.setProgress(0);
                            blue.setProgress(64);
                            Integer red = 255;
                            Integer green = 0;
                            Integer blue = 255;
                            lumnred.setText(String.valueOf(progress));
                            r.setText(String.valueOf(red));
                            lumngreen.setText(String.valueOf(progress));
                            g.setText(String.valueOf(green));
                            lumnblue.setText(String.valueOf(progress));
                            b.setText(String.valueOf(blue));
                            Socket.getOutputStream().write('l');
                        }
                        catch (IOException e)
                        {
                            msg("Error");
                        }
                    }
                }
            }
        });

        //Button - Color7
        c7.setOnClickListener(new OnClickListener(){
            public void onClick(View v)
            {
                if (Socket!=null)
                {
                    if(btnS1.getCurrentTextColor()==Color.RED || btnS2.getCurrentTextColor()==Color.RED ||btnS3.getCurrentTextColor()==Color.RED||btnS4.getCurrentTextColor()==Color.RED||btnS5.getCurrentTextColor()==Color.RED||btnS6.getCurrentTextColor()==Color.RED)
                    {
                        Toast.makeText(getApplicationContext(),"TURN OFF THE SEQUENCE", Toast.LENGTH_SHORT).show();
                    }
                    else
                        {
                        try
                        {
                            if (temp_ring == 0)
                            {
                                pr_redR1 = 5;
                            }
                            if (temp_ring == 1)
                            {
                                pr_redR2 = 5;
                            }
                            if (temp_ring == 0)
                            {
                                pr_greenR1 = 0;
                            }
                            if (temp_ring == 1)
                            {
                                pr_greenR2 = 0;
                            }
                            if (temp_ring == 0)
                            {
                                pr_blueR1 = 52;
                            }
                            if (temp_ring == 1)
                            {
                                pr_blueR2 = 52;
                            }
                            red.setProgress(5);
                            green.setProgress(0);
                            blue.setProgress(52);
                            Integer red = 19;
                            Integer green = 0;
                            Integer blue = 207;
                            lumnred.setText(String.valueOf(progress));
                            r.setText(String.valueOf(red));
                            lumngreen.setText(String.valueOf(progress));
                            g.setText(String.valueOf(green));
                            lumnblue.setText(String.valueOf(progress));
                            b.setText(String.valueOf(blue));
                            Socket.getOutputStream().write('m');
                        }
                        catch (IOException e)
                        {
                            msg("Error");
                        }
                    }
                }
            }
        });

        //SeekBar - SELECT RING NUMBER (default Ring1)
        ringnumber.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener(){
            @Override
            public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {

                if (fromUser==true)
                {
                    if(progress==0)
                        try
                        {
                            //Reset sekwencji
                            btnS1.setTextColor(Color.BLACK);
                            btnS1.setTextSize(14);
                            btnS2.setTextColor(Color.BLACK);
                            btnS2.setTextSize(14);
                            btnS3.setTextColor(Color.BLACK);
                            btnS3.setTextSize(14);
                            btnS4.setTextColor(Color.BLACK);
                            btnS4.setTextSize(14);
                            btnS5.setTextColor(Color.BLACK);
                            btnS5.setTextSize(14);
                            btnS6.setTextColor(Color.BLACK);
                            btnS6.setTextSize(14);

                            if(temp_S1R1==1)
                            {
                                btnS1.setTextColor(Color.RED);
                                btnS1.setTextSize(22);
                            }
                            if(temp_S2R1==1)
                            {
                                btnS2.setTextColor(Color.RED);
                                btnS2.setTextSize(22);
                            }
                            if(temp_S3R1==1)
                            {
                                btnS3.setTextColor(Color.RED);
                                btnS3.setTextSize(22);
                            }
                            if(temp_S4R1==1)
                            {
                                btnS4.setTextColor(Color.RED);
                                btnS4.setTextSize(22);
                            }
                            if(temp_S5R1==1)
                            {
                                btnS5.setTextColor(Color.RED);
                                btnS5.setTextSize(22);
                            }
                            if(temp_S6R1==1)
                            {
                                btnS6.setTextColor(Color.RED);
                                btnS6.setTextSize(22);
                            }
                            //brightness ring1
                            brightness.setProgress(pr_brightnessR1);
                            lumn.setText(String.valueOf(progress));
                            l.setText(String.valueOf(pr_brightnessR1*10+ "%"));
                            //red ring1
                            red.setProgress(pr_redR1);
                            lumnred.setText(String.valueOf(progress));
                            r.setText(String.valueOf(pr_redR1*4-1));
                            if(pr_redR1*4-1==-1)
                            {
                                r.setText(String.valueOf(0));
                            }
                            //green ring1
                            green.setProgress(pr_greenR1);
                            lumngreen.setText(String.valueOf(progress));
                            g.setText(String.valueOf(pr_greenR1*4-1));
                            if(pr_greenR1*4-1==-1)
                            {
                                g.setText(String.valueOf(0));
                            }
                            //blue ring1
                            blue.setProgress(pr_blueR1);
                            lumnblue.setText(String.valueOf(progress));
                            b.setText(String.valueOf(pr_blueR1*4-1));
                            if(pr_blueR1*4-1==-1)
                            {
                                b.setText(String.valueOf(0));
                            }
                            Toast.makeText(getApplicationContext(),"SELECTED: Ring1", Toast.LENGTH_SHORT).show();
                            Socket.getOutputStream().write('x');
                            temp_ring=0;
                        }
                        catch (IOException e)
                        {
                            msg("Error");
                        }
                    if(progress==1)
                    {
                        try
                        {
                            //Reset sekwencji
                            btnS1.setTextColor(Color.BLACK);
                            btnS1.setTextSize(14);
                            btnS2.setTextColor(Color.BLACK);
                            btnS2.setTextSize(14);
                            btnS3.setTextColor(Color.BLACK);
                            btnS3.setTextSize(14);
                            btnS4.setTextColor(Color.BLACK);
                            btnS4.setTextSize(14);
                            btnS5.setTextColor(Color.BLACK);
                            btnS5.setTextSize(14);
                            btnS6.setTextColor(Color.BLACK);
                            btnS6.setTextSize(14);

                            if(temp_S1R2==1)
                            {
                                btnS1.setTextColor(Color.RED);
                                btnS1.setTextSize(22);
                            }
                            if(temp_S2R2==1)
                            {
                                btnS2.setTextColor(Color.RED);
                                btnS2.setTextSize(22);
                            }
                            if(temp_S3R2==1)
                            {
                                btnS3.setTextColor(Color.RED);
                                btnS3.setTextSize(22);
                            }
                            if(temp_S4R2==1)
                            {
                                btnS4.setTextColor(Color.RED);
                                btnS4.setTextSize(22);
                            }
                            if(temp_S5R2==1)
                            {
                                btnS5.setTextColor(Color.RED);
                                btnS5.setTextSize(22);
                            }
                            if(temp_S6R2==1)
                            {
                                btnS6.setTextColor(Color.RED);
                                btnS6.setTextSize(22);
                            }

                            //brightness ring2
                            brightness.setProgress(pr_brightnessR2);
                            lumn.setText(String.valueOf(progress));
                            l.setText(String.valueOf(pr_brightnessR2*10+ "%"));
                            //red ring2
                            red.setProgress(pr_redR2);
                            lumnred.setText(String.valueOf(progress));
                            r.setText(String.valueOf(pr_redR2*4-1));
                            if(pr_redR2*4-1==-1)
                            {
                                r.setText(String.valueOf(0));
                            }
                            //green ring2
                            green.setProgress(pr_greenR2);
                            lumngreen.setText(String.valueOf(progress));
                            g.setText(String.valueOf(pr_greenR2*4-1));
                            if(pr_greenR2*4-1==-1)
                            {
                                g.setText(String.valueOf(0));
                            }
                            //blue ring2
                            blue.setProgress(pr_blueR2);
                            lumnblue.setText(String.valueOf(progress));
                            b.setText(String.valueOf(pr_blueR2*4-1));
                            if(pr_blueR2*4-1==-1)
                            {
                                b.setText(String.valueOf(0));
                            }
                            Toast.makeText(getApplicationContext(),"SELECTED: Ring2", Toast.LENGTH_SHORT).show();
                            Socket.getOutputStream().write('y');
                            temp_ring=1;
                        }
                        catch (IOException e)
                        {
                            msg("Error");
                        }
                    }
                }
            }

            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {

            }

            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {

            }
        });
    }

    private void Disconnect()
    {
        if (Socket!=null)
        {
            try
            {
                Socket.close(); //close connection
            }
            catch (IOException e)
            { msg("Error");}
        }
        finish(); //return to the first layout(paired)
    }

    public void turnOffLed()
    {
        if (Socket!=null)
            {
                try
                {
                    red.setProgress(0);
                    green.setProgress(0);
                    blue.setProgress(0);
                    brightness.setProgress(10);
                    l.setText(String.valueOf(100 + "%"));
                    changevar();
                    Socket.getOutputStream().write('O');
                    if(temp_ring==0)
                    {
                        pr_redR1=0;
                        pr_greenR1=0;
                        pr_blueR1=0;
                        pr_brightnessR1=10;
                        temp_S1R1=0;
                        temp_S2R1=0;
                        temp_S3R1=0;
                        temp_S4R1=0;
                        temp_S5R1=0;
                        temp_S6R1=0;
                    }
                    else
                    {
                        pr_redR2=0;
                        pr_greenR2=0;
                        pr_blueR2=0;
                        pr_brightnessR2=10;
                        temp_S1R2=0;
                        temp_S2R2=0;
                        temp_S3R2=0;
                        temp_S4R2=0;
                        temp_S5R2=0;
                        temp_S6R2=0;
                    }
                    //Reset sekwencji
                    btnS1.setTextColor(Color.BLACK);
                    btnS1.setTextSize(14);
                    btnS2.setTextColor(Color.BLACK);
                    btnS2.setTextSize(14);
                    btnS3.setTextColor(Color.BLACK);
                    btnS3.setTextSize(14);
                    btnS4.setTextColor(Color.BLACK);
                    btnS4.setTextSize(14);
                    btnS5.setTextColor(Color.BLACK);
                    btnS5.setTextSize(14);
                    btnS6.setTextColor(Color.BLACK);
                    btnS6.setTextSize(14);
                }
                catch (IOException e)
                {
                    msg("Error");
                }
        }
    }

    public void changevar()
    {
                    Integer pr=0;
                    lumnred.setText(String.valueOf(progress));
                    r.setText(String.valueOf(pr));
                    lumngreen.setText(String.valueOf(progress));
                    g.setText(String.valueOf(pr));
                    lumnblue.setText(String.valueOf(progress));
                    b.setText(String.valueOf(pr));
                    try
                    {
                        Socket.getOutputStream().write('R');
                        Socket.getOutputStream().write(Integer.valueOf(pr));
                        Socket.getOutputStream().write('G');
                        Socket.getOutputStream().write(Integer.valueOf(pr));
                        Socket.getOutputStream().write('B');
                        Socket.getOutputStream().write(Integer.valueOf(pr));
                    }
                    catch (IOException e)
                    {
                        msg("Error");
                    }
    }

    // fast way to call Toast
    private void msg(String s)
    {
        Toast.makeText(getApplicationContext(),s,Toast.LENGTH_LONG).show();
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {

        getMenuInflater().inflate(R.menu.menu_led_control, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {

        int id = item.getItemId();

        if (id == R.id.action_settings) {
            return true;
        }
        return super.onOptionsItemSelected(item);
    }


    private class ConnectBT extends AsyncTask<Void, Void, Void>
    {
        private boolean ConnectSuccess = true;

        @Override
        protected void onPreExecute()
        {
            progress = ProgressDialog.show(ledControl.this, "Connecting...", "Please wait!!!");
        }

        @Override
        protected Void doInBackground(Void... devices)
        {
            try
            {
                if (Socket == null || !isBtConnected)
                {
                 myBluetooth = BluetoothAdapter.getDefaultAdapter();
                 BluetoothDevice dispositivo = myBluetooth.getRemoteDevice(address);
                 Socket = dispositivo.createInsecureRfcommSocketToServiceRecord(myUUID);
                 BluetoothAdapter.getDefaultAdapter().cancelDiscovery();
                 Socket.connect();//start connection
                }
            }
            catch (IOException e)
            {
                ConnectSuccess = false;
            }
            return null;
        }
        @Override
        protected void onPostExecute(Void result)
        {
            super.onPostExecute(result);

            if (!ConnectSuccess)
            {
                msg("Connection Failed");
                finish();
            }
            else
            {
                msg("Connected");
                isBtConnected = true;
            }
            progress.dismiss();
        }
    }
}