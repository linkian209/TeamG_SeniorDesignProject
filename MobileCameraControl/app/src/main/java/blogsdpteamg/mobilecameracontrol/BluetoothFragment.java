package blogsdpteamg.mobilecameracontrol;

import android.app.Activity;
import android.bluetooth.BluetoothDevice;
import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.bluetooth.BluetoothAdapter;
import android.widget.ListView;

import java.util.ArrayList;


public class BluetoothFragment extends Fragment {
    /**
     * The fragment argument representing the section number for this
     * fragment.
     */
    private static final String ARG_SECTION_NUMBER = "section_number";

    /**
     * Privates for the fragment
     */
    private static BluetoothAdapter bTAdapter;
    private ListView mListView;
    private ArrayList<BluetoothDevice> mDeviceList;


    /**
     * Returns a new instance of this fragment for the given section
     * number.
     */
    public static BluetoothFragment newInstance(BluetoothAdapter adapter) {
        BluetoothFragment fragment = new BluetoothFragment();
        bTAdapter = adapter;
        return fragment;
    }

    public BluetoothFragment() {
    }

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);


    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        View rootView = inflater.inflate(R.layout.fragment_placeholder, container, false);
        return rootView;
    }

    @Override
    public void onAttach(Activity activity) {
        super.onAttach(activity);
        ((MainActivity) activity).onSectionAttached(
                getArguments().getInt(ARG_SECTION_NUMBER));
    }
}
