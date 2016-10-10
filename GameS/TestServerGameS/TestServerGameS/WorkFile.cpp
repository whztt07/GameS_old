#include "stdafx.h"


#include "WorkFile.h"
#include "GeoData.h"


GeoData& WorkFile::ReadGeoData(){
	
	FILE *f;

	int n = 8;
	System::IO::FileStream^ fs = gcnew System::IO::FileStream("geoData.geo", System::IO::FileMode::OpenOrCreate);
	System::IO::BinaryReader^ reader = gcnew System::IO::BinaryReader(fs);
	n = reader->ReadInt32();
	GeoData *geoData = new GeoData();
	geoData->size_z = n;
	n = reader->ReadInt32();
	geoData->size_x = n;

	for (int i = 0; i < geoData->size_z*geoData->size_x; i++){
		int n;
		byte bytes[(4 + 9 * 64)];
		array<unsigned char, 1> ^cha = gcnew array<unsigned char, 1>((4 + 9 * 64));
		int iter = 0;
		for (int g = 0; g < 4 + 9 * 64; g++){
			cha[g] = reader->ReadByte();
		}
		n = System::BitConverter::ToInt32(cha, iter);
		iter += 4;
		GeoCell _geoCells[64];
		for (int h = 0; h < 64; h++){
			_geoCells[h] = GeoCell();
		}
		for (int j = 0; j < 64; j++){
			bool an = true;
			an = System::BitConverter::ToBoolean(cha, iter);
			iter++;
			
			_geoCells[j].exist = an;
			
			an = System::BitConverter::ToBoolean(cha, iter);
			iter++;
			_geoCells[j].north = an;
			an = System::BitConverter::ToBoolean(cha, iter);
			iter++;
			
			_geoCells[j].south = an;
			an = System::BitConverter::ToBoolean(cha, iter);
			iter++;
			
			_geoCells[j].west = an;
			an = System::BitConverter::ToBoolean(cha, iter);
			iter++;
			
			_geoCells[j].east = an;
			float fl = 0;
			
			fl = System::BitConverter::ToSingle(cha, iter);
			iter += 4;
			_geoCells[j].height = fl;
		}
		geoData->geoCubs.push_back(GeoCube(n, _geoCells));
	}
	
	return *geoData;
}