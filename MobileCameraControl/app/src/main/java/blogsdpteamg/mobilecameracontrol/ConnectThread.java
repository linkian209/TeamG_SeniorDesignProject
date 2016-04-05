package blogsdpteamg.mobilecameracontrol;

import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothSocket;
import android.os.Handler;
import android.util.Log;

import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.UUID;

public class ConnectThread extends Thread{

    private final BluetoothDevice bTDevice;
    private final BluetoothSocket bTSocket;
    private final InputStream inputStream;
    private final OutputStream outputStream;
    private final Handler mHandler;

    private int MESSAGE_READ = 2;

    public ConnectThread(BluetoothDevice bTDevice, UUID UUID, Handler m_Handler) {
        // First Create Socket and null the streams
        BluetoothSocket tmp = null;
        InputStream tempIn = null;
        OutputStream tempOut = null;
        mHandler = m_Handler;
        this.bTDevice = bTDevice;

        try {
            tmp = this.bTDevice.createRfcommSocketToServiceRecord(UUID);
        }
        catch (IOException e) {
            Log.d("CONNECTTHREAD", "Could not start listening for RFCOMM");
        }
        bTSocket = tmp;

        // Now Make the streams
        try {
            tempIn = bTSocket.getInputStream();
            tempOut = bTSocket.getOutputStream();
        }
        catch(IOException e)
        {

        }

        inputStream = tempIn;
        outputStream = tempOut;
    }

    public boolean connect() {

        try {
            bTSocket.connect();
        } catch(IOException e) {
            Log.d("CONNECTTHREAD","Could not connect: " + e.toString());
            try {
                bTSocket.close();
            } catch(IOException close) {
                Log.d("CONNECTTHREAD", "Could not close connection:" + e.toString());
                return false;
            }
        }
        return true;
    }

    public boolean cancel() {
        try {
            bTSocket.close();
        } catch(IOException e) {
            return false;
        }
        return true;
    }

    public void run()
    {
        byte[] buffer = new byte[260];
        int bytes = 0;
        int begin = 0;
        ByteArrayOutputStream baos = new ByteArrayOutputStream();

        // Listen to Input stream until we hit an exception
        while(true)
        {
            try
            {
                // Read bytes
                /*
                while((bytes = inputStream.read(buffer, 0,buffer.length)) > -1)
                {
                    Log.d("Current Buffer",new String(buffer));
                    baos.write(buffer,0,bytes);
                    baos.flush();
                }
                */
                bytes += inputStream.read(buffer, bytes, buffer.length - bytes);
                for(int i = begin; i < bytes; i++) {
                    if(buffer[i] == "$".getBytes()[0]) {
                        mHandler.obtainMessage(MESSAGE_READ, begin, i, buffer).sendToTarget();
                        begin = i + 1;
                        if(i == bytes - 1) {
                            bytes = 0;
                            begin = 0;
                        }
                    }
                }

                //bytes = inputStream.read(buffer);
                // Send bytes to main activity
                String temp = new String(buffer);
                Log.d("Thread","Received: ["+temp+"]");
                mHandler.obtainMessage(MESSAGE_READ,bytes,-1,buffer)
                .sendToTarget();
            }
            catch (IOException e)
            {
                Log.d("MESSAGE READ FAIL",e.getMessage());
            }
        }
    }

    public void write(byte[] bytes)
    {
        try
        {
            outputStream.write(bytes);
        }
        catch (IOException e)
        {

        }
    }

    public boolean isConnected()
    {
        return bTSocket.isConnected();
    }

}