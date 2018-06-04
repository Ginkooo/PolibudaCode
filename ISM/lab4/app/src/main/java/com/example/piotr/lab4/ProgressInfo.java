package com.example.piotr.lab4;

import android.os.Parcel;
import android.os.Parcelable;

public class ProgressInfo implements Parcelable {

    public long fetched;
    public long size;
    public String result;

    public ProgressInfo(long current, long size, String result) {
        this.fetched = current;
        this.size = size;
        this.result = result;
    }

    public ProgressInfo(Parcel parcel) {
        fetched = parcel.readLong();
        size = parcel.readLong();
        result = parcel.readString();
    }

    @Override
    public int describeContents() {
        return 0;
    }

    @Override
    public void writeToParcel(Parcel dest, int flags) {
        dest.writeLong(fetched);
        dest.writeLong(size);
        dest.writeString(result);
    }

    public static final Parcelable.Creator<ProgressInfo> CREATOR = new Creator<ProgressInfo>() {
        @Override
        public ProgressInfo createFromParcel(Parcel source) {
            return new ProgressInfo(source);
        }

        @Override
        public ProgressInfo[] newArray(int size) {
            return new ProgressInfo[size];
        }
    };
}
