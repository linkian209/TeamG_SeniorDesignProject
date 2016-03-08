package blogsdpteamg.mobilecameracontrol;

import android.app.Activity;
import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;


public class MainScreenFragment extends Fragment {
    /**
     * The fragment argument representing the section number for this
     * fragment.
     */
    private static final String ARG_SECTION_NUMBER = "section_number";

    /**
     * Interface Listener
     */
    private OnFragmentInteractionListener mListener;
    /**
     * Returns a new instance of this fragment for the given section
     * number.
     */
    public static MainScreenFragment newInstance(int sectionNumber) {
        MainScreenFragment fragment = new MainScreenFragment();
        Bundle args = new Bundle();
        args.putInt(ARG_SECTION_NUMBER, sectionNumber);
        fragment.setArguments(args);
        return fragment;
    }

    public MainScreenFragment() {
    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        View rootView = inflater.inflate(R.layout.fragment_main, container, false);

        // Create Button Listeners
        Button up = (Button) rootView.findViewById(R.id.buttonUp);
        up.setOnClickListener(new View.OnClickListener(){
            @Override
            public void onClick(View v)
            {
                if(mListener != null)
                {
                    mListener.onButtonClick("UP");
                }
            }
        });

        Button down = (Button) rootView.findViewById(R.id.buttonDown);
        down.setOnClickListener(new View.OnClickListener(){
            @Override
            public void onClick(View v)
            {
                if(mListener != null)
                {
                    mListener.onButtonClick("DOWN");
                }
            }
        });

        Button left = (Button) rootView.findViewById(R.id.buttonLeft);
        left.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v)
            {
                if(mListener != null)
                {
                    mListener.onButtonClick("LEFT");
                }
            }
        });

        Button right = (Button) rootView.findViewById(R.id.buttonRight);
        right.setOnClickListener(new View.OnClickListener(){
            @Override
            public void onClick(View v)
            {
                if(mListener != null)
                {
                    mListener.onButtonClick("RIGHT");
                }
            }
        });

        Button capture = (Button) rootView.findViewById(R.id.buttonCapture);
        capture.setOnClickListener(new View.OnClickListener(){
            @Override
            public void onClick(View v)
            {
                if(mListener != null)
                {
                    mListener.onButtonClick("CAPTURE");
                }
            }
        });

        return rootView;
    }

    @Override
    public void onAttach(Activity activity) {
        super.onAttach(activity);
        try {
            mListener = (OnFragmentInteractionListener) activity;
        } catch (ClassCastException e) {
            throw new ClassCastException(activity.toString()
                    + " must implement OnFragmentInteractionListener");
        }
        ((MainActivity) activity).onSectionAttached(
                getArguments().getInt(ARG_SECTION_NUMBER));
    }

    @Override
    public void onDetach() {
        super.onDetach();
        mListener = null;
    }

    /**
     * Fragment Interaction Listener Interface
     */
    public interface OnFragmentInteractionListener
    {
        void onButtonClick(String id);
    }
}
