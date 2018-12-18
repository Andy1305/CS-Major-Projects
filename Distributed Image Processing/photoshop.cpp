#include<mpi.h>
#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<vector>

using namespace std;


int main(int argc, char** argv)
{
	int rank, np, node, nr_ops, width, height, nr_lines, offset, size,
	    parent = -1, tag, filter[3][3], filter_offset, colorscale,
	    total_nr_lines = 0;
	int* top_line;
	int* bottom_line;
	int* my_end;
	int* his_end;
	int** pixels;
	int** pixels2;
	char c;
	string line, operation, in_img, out_img;
	ifstream in, img_in;
	ofstream out, img_out;
	vector<int> friends;
	vector<string> ops;
	MPI_Status status;
	
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &np);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	
	// Fiecare nod isi afla vecinii, citindu-i din fisier.
	in.open(argv[1]);
	
	if(in.is_open())
	{
		while((in >> node) && (node != rank)) 
		{
			in.ignore(256, '\n');
		}
		
		in >> c;
		
		getline(in, line);
		
		in.close();
	}
			
	istringstream iss(line);
	
	while(iss >> node)
	{
		friends.push_back(node);
	}

	my_end = new int[np]();
	his_end = new int[np]();

	if(rank == 0)
	{
		// Nodul 0 citeste operatiile.
		in.open(argv[2]);
	
		if(in.is_open())
		{
			in >> nr_ops;
			
			getline(in, line);

			for(int i = 0; i < nr_ops; i++)
			{
				getline(in, line);
				ops.push_back(line);
			}
			
			in.close();
		}

		// Trimit numarul de operatii.
		for(int i = 0; i < friends.size(); i++)
		{
			MPI_Send(&nr_ops, 1, MPI_INT, friends[i], 1, MPI_COMM_WORLD);
		}
		
		// Iau pe rand fiecare linie din imagini.in.
		for(int i = 0; i < ops.size(); i++)
		{
			offset = 0;							// de la ce linie incep
		
			istringstream iss(ops[i]);
			
			iss >> operation;
			iss >> in_img;
			iss >> out_img;
			
			if(operation.compare("sobel") == 0)
			{
				tag = 2;
			}
			else if(operation.compare("mean_removal") == 0)
			{
				tag = 3;
			}	

			img_in.open(in_img.c_str());
			img_out.open(out_img.c_str());

			getline(img_in, line);
			img_out << line << endl;
			
			getline(img_in, line);
			img_out << line << endl;
			
			img_in >> width;
			img_in >> height;
			
			img_out << width << " " << height << endl;
			
			img_in >> colorscale;
			img_out << colorscale << endl;

			pixels = new int*[height];
			
			for(int j = 0; j < height; j++)
			{
				pixels[j] = new int[width]();
			}

			// Citesc toti pixelii.
			for(int j = 0; j < height; j++)
			{
				for(int k = 0; k < width; k++)
				{
					img_in >> pixels[j][k];
				}
			}
			
			img_in.close();

			if(height >= friends.size())				// daca sunt mai multe linii decat procese
			{
				size = friends.size();
				
				nr_lines = height / friends.size();
			}
			else							// daca sunt mai putine linii decat procese
			{
				size = height;
				
				nr_lines = 1;
			}
			
			// Trimit la copii numarul de pixeli, liniile granita si pixelii.
			for(int j = 0; j < size; j++)
			{
				if((height >= friends.size()) && (height % friends.size() != 0) && (j == friends.size() - 1))
				{
					nr_lines += height % size;
				}
						
				// Trimit numarul de linii.	
				MPI_Send(&nr_lines, 1, MPI_INT, friends[j], tag, MPI_COMM_WORLD);
					
				// Trimit numarul de coloane.
				MPI_Send(&width, 1, MPI_INT, friends[j], tag, MPI_COMM_WORLD);		
					
				top_line = new int[width]();
				bottom_line = new int[width]();
					
				// Trimit liniile de granita.
				if(j == 0)					// prima parte a imaginii
				{
					// Trimit linia de sus.
					MPI_Send(top_line, width, MPI_INT, friends[0], tag, MPI_COMM_WORLD);
					
					// Trimit linia de jos.	
					if(nr_lines == height)
					{
						MPI_Send(bottom_line, width, MPI_INT, friends[0], tag, MPI_COMM_WORLD);
					}
					else
					{
						MPI_Send(pixels[nr_lines], width, MPI_INT, friends[0], tag, MPI_COMM_WORLD);
					}
				}
				else if(j == size - 1)				// ultima parte a imaginii.
				{
					// Trimit linia de sus.
					MPI_Send(pixels[height - nr_lines - 1], width, MPI_INT, friends[j], tag, MPI_COMM_WORLD);
						
					// Trimit linia de jos.
					MPI_Send(bottom_line, width, MPI_INT, friends[j], tag, MPI_COMM_WORLD);
				}
				else						// mijlocul imaginii
				{
					// Trimit linia de sus.
					MPI_Send(pixels[offset - 1], width, MPI_INT, friends[j], tag, MPI_COMM_WORLD);
						
					// Trimit linia de jos.
					MPI_Send(pixels[offset + nr_lines], width, MPI_INT, friends[j], tag, MPI_COMM_WORLD);
				}

				// Trimit pixelii.
				for(int k = 0; k < nr_lines; k++)
				{
					MPI_Send(pixels[k + offset], width, MPI_INT, friends[j], tag, MPI_COMM_WORLD);
				}
				
				offset += nr_lines;
			}

			offset = 0;
			
			if(height >= friends.size())			// daca sunt mai multe linii ca procese
			{
				size = friends.size();
				
				nr_lines = height / friends.size();
			}
			else						// daca sunt mai putine linii ca procese
			{
				size = height;
				
				nr_lines = 1;
			}
			
			// Primesc de la copii parti ale imaginii si le reunesc.
			for(int j = 0; j < size; j++)
			{
				if((height >= friends.size()) && (height % friends.size() != 0) && (j == friends.size() - 1))
				{
					nr_lines += height % friends.size();
				}
					
				for(int k = 0; k < nr_lines; k++)
				{
					MPI_Recv(pixels[k + offset], width, MPI_INT, friends[j], tag, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
				}
				
				offset += nr_lines;
			}

			// Scriu in fisier imaginea modificata.
			for(int j = 0; j < height; j++)
			{
				for(int k = 0; k < width; k++)
				{
					img_out << pixels[j][k] << endl;
				}
			}

			img_out.close();

			for(int j = 0; j < height; j++)
			{
				delete[] pixels[j];
			}
			
			delete[] pixels;
			delete[] top_line;
			delete[] bottom_line;
		}
		
		// Trimit tagul de terminare si astept statisticile.
		tag = 0;
		
		for(int i = 0; i < friends.size(); i++)
		{
			MPI_Send(my_end, np, MPI_INT, friends[i], tag, MPI_COMM_WORLD);
		}
		
		for(int i = 0; i < friends.size(); i++)
		{
			MPI_Recv(his_end, np, MPI_INT, friends[i], tag, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			
			for(int j = 0; j < np; j++)
			{
				if(his_end[j] != 0)
				{
					my_end[j] = his_end[j];
				}
			}
		}
		
		// Scriu in fisier statistica.
		out.open(argv[3]);
		
		for(int i = 0; i < np; i++)
		{
			out << i << ": " << my_end[i] << endl;
		}
		
		out.close();
		
		delete[] my_end;
		delete[] his_end;
	}
	else								// daca rankul nu e 0
	{
		if(friends.size() != 1)					// daca nu e frunza
		{
			// Primesc numarul de operatii.
			MPI_Recv(&nr_ops, 1, MPI_INT, MPI_ANY_SOURCE, 1, MPI_COMM_WORLD, &status);

			parent = status.MPI_SOURCE;

			// Sterg parintele din vecini.
			for(int i = 0; i < friends.size(); i++)
			{
				if(parent == friends[i])
				{
					friends.erase(friends.begin() + i);
				}
			}
			
			// Trimit numarul de operatii.
			for(int i = 0; i < friends.size(); i++)
			{
				MPI_Send(&nr_ops, 1, MPI_INT, friends[i], 1, MPI_COMM_WORLD);
			}

			for(int i = 0; i < nr_ops; i++)
			{
				offset = 0;
				
				// Primesc de la parinte numarul de linii.
				MPI_Recv(&height, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);

				parent = status.MPI_SOURCE;
				tag = status.MPI_TAG;
			
				// Primesc numarul de coloane.
				MPI_Recv(&width, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
			
				top_line = new int[width]();
				bottom_line = new int[width]();
			
				// Primesc liniile de granita.
				MPI_Recv(top_line, width, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
				MPI_Recv(bottom_line, width, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);

				pixels = new int*[height];
			
				for(int j = 0; j < height; j++)
				{
					pixels[j] = new int[width]();
				}
			
				// Primesc toti pixelii.			
				for(int j = 0; j < height; j++)
				{
					MPI_Recv(pixels[j], width, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
				}

				if(height >= friends.size())		// daca sunt mai multe linii ca procese
				{
					size = friends.size();
				
					nr_lines = height / friends.size();
				}
				else					// daca sunt mai putine linii ca procese
				{
					size = height;
				
					nr_lines = 1;
				}

				// Trimit mai departe, la copii.
				for(int j = 0; j < size; j++)
				{
					if((height >= friends.size()) && (height % friends.size() != 0) && (j == friends.size() - 1))
					{
						nr_lines += height % friends.size();
					}
						
					// Trimit numarul de linii.	
					MPI_Send(&nr_lines, 1, MPI_INT, friends[j], tag, MPI_COMM_WORLD);
					
					// Trimit numarul de coloane.
					MPI_Send(&width, 1, MPI_INT, friends[j], tag, MPI_COMM_WORLD);

					// Trimit liniile de granita.
					if(j == 0)			// prima parte a imaginii
					{
						// Trimit linia de sus.
						MPI_Send(top_line, width, MPI_INT, friends[0], tag, MPI_COMM_WORLD);
						
						if(nr_lines == height)
						{
							// Trimit linia de jos.
							MPI_Send(bottom_line, width, MPI_INT, friends[0], tag, MPI_COMM_WORLD);
						}
						else
						{
							// Trimit linia de jos.
							MPI_Send(pixels[nr_lines], width, MPI_INT, friends[0], tag, MPI_COMM_WORLD);
						}
					}
					else if(j == size - 1)		// ultima parte a imaginii
					{
						// Trimit linia de sus.
						MPI_Send(pixels[height - nr_lines - 1], width, MPI_INT, friends[j], tag, MPI_COMM_WORLD);
							
						// Trimit linia de jos.
						MPI_Send(bottom_line, width, MPI_INT, friends[j], tag, MPI_COMM_WORLD);
					}
					else				// mijlocul imaginii
					{
						// Trimit linia de sus.
						MPI_Send(pixels[offset - 1], width, MPI_INT, friends[j], tag, MPI_COMM_WORLD);
						
						// Trimit linia de jos.
						MPI_Send(pixels[offset + nr_lines], width, MPI_INT, friends[j], tag, MPI_COMM_WORLD);
					}

					// Trimit pixelii.
					for(int k = 0; k < nr_lines; k++)
					{
						MPI_Send(pixels[k + offset], width, MPI_INT, friends[j], tag, MPI_COMM_WORLD);
					}
					
					offset += nr_lines;
				}

				if(height >= friends.size())		// daca sunt mai multe linii ca procese
				{
					size = friends.size();
				
					nr_lines = height / friends.size();
				}
				else					// daca sunt mai putine linii ca procese
				{
					size = height;
				
					nr_lines = 1;
				}
			
				offset = 0;
			
				// Primesc inapoi de la copii partile imaginii si le reunesc.
				for(int j = 0; j < size; j++)
				{
					if((height >= friends.size()) && (height % friends.size() != 0) && (j == friends.size() - 1))
					{
						nr_lines += height % friends.size();
					}
					
					for(int k = 0; k < nr_lines; k++)
					{
						MPI_Recv(pixels[k + offset], width, MPI_INT, friends[j], tag, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
					}
					
					offset += nr_lines;
				}
				
				// Trimit la parinte.
				for(int j = 0; j < height; j++)
				{
					MPI_Send(pixels[j], width, MPI_INT, parent, tag, MPI_COMM_WORLD);
				}
				
				for(int j = 0; j < height; j++)
				{
					delete[] pixels[j];
				}
				
				delete[] top_line;
				delete[] bottom_line;
				delete[] pixels;
			}
				
			// Primesc mesaje de terminare.
			MPI_Recv(my_end, np, MPI_INT, parent, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		
			// Trimit mesaj de terminare.
			for(int i = 0; i < friends.size(); i++)
			{
				MPI_Send(my_end, np, MPI_INT, friends[i], 0, MPI_COMM_WORLD);
			}
			
			// Primesc statistica.
			for(int i = 0; i < friends.size(); i++)
			{
				MPI_Recv(his_end, np, MPI_INT, friends[i], 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			
				for(int j = 0; j < np; j++)
				{
					if(his_end[j] != 0)
					{
						my_end[j] = his_end[j];
					}
				}
			}
			
			MPI_Send(my_end, np, MPI_INT, parent, 0, MPI_COMM_WORLD);
			
			delete[] my_end;
			delete[] his_end;
		}
		else							// daca e frunza
		{
			// Primesc numarul de operatii.
			MPI_Recv(&nr_ops, 1, MPI_INT, MPI_ANY_SOURCE, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

			for(int i = 0; i < nr_ops; i++)
			{
				// Primesc de la parinte numarul de linii.
				MPI_Recv(&height, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
				total_nr_lines += height;
				
				parent = status.MPI_SOURCE;
				tag = status.MPI_TAG;
			
				// Primesc numarul de coloane.
				MPI_Recv(&width, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
			
				top_line = new int[width]();
				bottom_line = new int[width]();
			
				// Primesc liniile de granita.
				MPI_Recv(top_line, width, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
				MPI_Recv(bottom_line, width, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);

				pixels = new int*[height];
				pixels2 = new int*[height];
				
				for(int j = 0; j < height; j++)
				{
					pixels[j] = new int[width]();
					pixels2[j] = new int[width]();
				}

				// Primesc toti pixelii.			
				for(int j = 0; j < height; j++)
				{
					MPI_Recv(pixels[j], width, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
				}
			
				// Aplic filtrul.
				if(tag == 2)				// sobel
				{
					filter[0][0] =  1;
					filter[0][1] =  0;
					filter[0][2] = -1;
					filter[1][0] =  2;
					filter[1][1] =  0;
					filter[1][2] = -2;
					filter[2][0] =  1;
					filter[2][1] =  0;
					filter[2][2] = -1;
							
					filter_offset = 127;
				}
				else if(tag == 3)			// mean_removal
				{
					filter[0][0] = -1;
					filter[0][1] = -1;
					filter[0][2] = -1;
					filter[1][0] = -1;
					filter[1][1] =  9;
					filter[1][2] = -1;
					filter[2][0] = -1;
					filter[2][1] = -1;
					filter[2][2] = -1;
							
					filter_offset = 0;
				}

				for(int j = 0; j < height; j++)
				{
					for(int k = 0; k < width; k++)
					{
						if(j == 0)
						{
							if(k == 0)			// stanga sus
							{
								pixels2[j][k] = (top_line[k] * filter[0][1] +
										 top_line[k + 1] * filter[0][2] +	
										 pixels[j][k] * filter[1][1] +
									         pixels[j][k + 1] * filter[1][2] +
									         pixels[j + 1][k] * filter[2][1] +
									         pixels[j + 1][k + 1] * filter[2][2]) / 1 + filter_offset;
							}
							else if(k == width - 1) 	// dreapta sus
							{
								pixels2[j][k] = (top_line[k - 1] * filter[0][0] +
										 top_line[k] * filter[0][1] +
										 pixels[j][k - 1] * filter[1][0] +
									         pixels[j][k] * filter[1][1] +
									         pixels[j + 1][k - 1] * filter[2][0] +
									         pixels[j + 1][k] * filter[2][1]) / 1 + filter_offset;
							}
							else
							{
								pixels2[j][k] = (top_line[k - 1] * filter[0][0] +
										 top_line[k] * filter[0][1] +
										 top_line[k + 1] * filter[0][2] +
										 pixels[j][k - 1] * filter[1][0] +
									         pixels[j][k] * filter[1][1] +
									         pixels[j][k + 1] * filter[1][2] +
									         pixels[j + 1][k - 1] * filter[2][0] +
									         pixels[j + 1][k] * filter[2][1] +
									         pixels[j + 1][k + 1] * filter[2][2]) / 1 + filter_offset;
							}
						}
						else if(j == height - 1)
						{
							if(k == 0)			// stanga jos
							{
								pixels2[j][k] = (bottom_line[k] * filter[2][1] +
										 bottom_line[k + 1] * filter[2][2] +
										 pixels[j - 1][k] * filter[0][1] +
									         pixels[j - 1][k + 1] * filter[0][2] +
									         pixels[j][k] * filter[1][1] +
									         pixels[j][k + 1] * filter[1][2]) / 1 + filter_offset;
							}
							else if(k == width - 1)		// dreapta jos
							{
								pixels2[j][k] = (bottom_line[k - 1] * filter[2][0] +
										 bottom_line[k] * filter[2][1] +
										 pixels[j - 1][k - 1] * filter[0][0] +
									         pixels[j - 1][k] * filter[0][1] +
									         pixels[j][k - 1] * filter[1][0] +
									         pixels[j][k] * filter[1][1]) / 1 + filter_offset;
							}
							else
							{
								pixels2[j][k] = (bottom_line[k - 1] * filter[2][0] +
										 bottom_line[k] * filter[2][1] +
										 bottom_line[k + 1] * filter[2][2] +
										 pixels[j - 1][k - 1] * filter[0][0] +
									         pixels[j - 1][k] * filter[0][1] +
									         pixels[j - 1][k + 1] * filter[0][2] +
									         pixels[j][k - 1] * filter[1][0] +
									         pixels[j][k] * filter[1][1] +
									         pixels[j][k + 1] * filter[1][2]) / 1 + filter_offset;
							}
						}
						else					// linie din mijloc
						{
							if(k == 0)
							{
								pixels2[j][k] = (pixels[j - 1][k] * filter[0][1] +
									         pixels[j - 1][k + 1] * filter[0][2] +
									         pixels[j][k] * filter[1][1] +
									         pixels[j][k + 1] * filter[1][2] +
									         pixels[j + 1][k] * filter[2][1] +
									         pixels[j + 1][k + 1] * filter[2][2]) / 1 + filter_offset;
							}
							else if (k == width - 1)
							{
								pixels2[j][k] = (pixels[j - 1][k - 1] * filter[0][0] +
									         pixels[j - 1][k] * filter[0][1] +
									         pixels[j][k - 1] * filter[1][0] +
									         pixels[j][k] * filter[1][1] +
									         pixels[j + 1][k - 1] * filter[2][0] +
									         pixels[j + 1][k] * filter[2][1]) / 1 + filter_offset;
							}
							else
							{
								pixels2[j][k] = (pixels[j - 1][k - 1] * filter[0][0] +
									         pixels[j - 1][k] * filter[0][1] +
									         pixels[j - 1][k + 1] * filter[0][2] +
									         pixels[j][k - 1] * filter[1][0] +
									         pixels[j][k] * filter[1][1] +
									         pixels[j][k + 1] * filter[1][2] +
									         pixels[j + 1][k - 1] * filter[2][0] +
									         pixels[j + 1][k] * filter[2][1] +
									         pixels[j + 1][k + 1] * filter[2][2]) / 1 + filter_offset;
							}
						}
						
						// In caz ca se depaseste intervalul.
						if(pixels2[j][k] < 0)
						{
							pixels2[j][k] = 0;
						}
								
						if(pixels2[j][k] > 255)
						{
							pixels2[j][k] = 255;
						}
					}
				}

				// Trimit la parinte imaginea procesata.
				for(int j = 0; j < height; j++)
				{
					MPI_Send(pixels2[j], width, MPI_INT, parent, tag, MPI_COMM_WORLD);
				}

				for(int j = 0; j < height; j++)
				{
					delete[] pixels[j];
					delete[] pixels2[j];
				}
				
				delete[] top_line;
				delete[] bottom_line;
				delete[] pixels;
				delete[] pixels2;
			}
					
			// Primesc mesaj de terminare.
			MPI_Recv(my_end, np, MPI_INT, parent, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			
			// Adaug numarul total de linii procesate, ale frunzei.
			my_end[rank] = total_nr_lines;

			// Trimit statistica.
			MPI_Send(my_end, np, MPI_INT, parent, 0, MPI_COMM_WORLD);
		}
	}
	
	MPI_Finalize();
	
	return 0;
}
