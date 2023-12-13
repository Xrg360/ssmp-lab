#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void main()
{
	FILE *obj, *out;																	  // File pointer to read the object file
	int i, j, start, saddr2, cadr2;												  // Variables for iteration and memory addresses
	char line[100], name[10], name2[10], saddr[10], mask[15], code[10], cadr[10]; // Arrays to store different values

	printf("Enter the program name:");
	scanf("%s", name); // Read the program name from the user

	obj = fopen("obj_program.txt", "r"); // Open the object file for reading
	out = fopen("output.txt", "w+"); // Open the output file for writing	
	fscanf(obj, "%s", line);				// Read the first line from the object file

	// Extract the program name from the first line of the object file
	for (i = 0, j = 2; i < 6; i++, j++)
		name2[i] = line[j];
	name2[i] = '\0';

	// Check if the entered program name matches the program name in the object file
	if (strcmp(name, name2) == 0)
	{
		printf("Enter the starting address:");
		scanf("%x", &start); // Read the starting address from the user

		do
		{
			fscanf(obj, "%s", line); // Read label line from the object file

			if (line[0] == 'T') // Check if the line represents label text record
			{
				// Extract the starting address from the text record
				for (i = 2, j = 0; i < 8, j < 6; i++, j++)
					saddr[j] = line[i];
				saddr[j] = '\0';

				// Calculate the actual starting address by adding the user-provided starting address
				saddr2 = (int)strtol(saddr, NULL, 16) + start;

				mask[0] = '\0';

				// Extract the modification bits from the text record
				for (i = 12; i < 15; i++)
				{
					switch (line[i])
					{
					case '0':
						strcat(mask, "0000");
						break;
					case '1':
						strcat(mask, "0001");
						break;
					case '2':
						strcat(mask, "0010");
						break;
					case '3':
						strcat(mask, "0011");
						break;
					case '4':
						strcat(mask, "0100");
						break;
					case '5':
						strcat(mask, "0101");
						break;
					case '6':
						strcat(mask, "0110");
						break;
					case '7':
						strcat(mask, "0111");
						break;
					case '8':
						strcat(mask, "1000");
						break;
					case '9':
						strcat(mask, "1001");
						break;
					case 'a':
						strcat(mask, "1010");
						break;
					case 'b':
						strcat(mask, "1011");
						break;
					case 'c':
						strcat(mask, "1100");
						break;
					case 'd':
						strcat(mask, "1101");
						break;
					case 'e':
						strcat(mask, "1110");
						break;
					case 'f':
						strcat(mask, "1111");
						break;
					}
				}

				i = 16;
				int k = 0; // For iterating through mask

				// Process the object code in the text record
				while (line[i] != '$')
				{
					if (line[i] != '^')
					{
						// Extract the object code and address from the text record
						for (j = 0, i; j < 6; j++, i++)
						{
							code[j] = line[i];
							if (j > 1)
								cadr[j - 2] = line[i];
						}
						code[j] = '\0';
						cadr[j - 2] = '\0';

						// Check if the modification bit is set for the current object code
						if (mask[k] == '1')
						{
							// Calculate the actual address by adding the user-provided starting address
							cadr2 = (int)strtol(cadr, NULL, 16) + start;

							// Print the modified object code with the actual address
							printf("%x\t%operand%operand%x\n", saddr2, code[0], code[1], cadr2);
							fprintf(out, "%x\t%operand%operand%x\n", saddr2, code[0], code[1], cadr2);							
						}
						else
						{
							// Print the object code with the original address
							printf("%x\t%s\n", saddr2, code);
							fprintf(out, "%x\t%s\n", saddr2, code);							
						}

						saddr2 += 0x3; // Increment the address by 3 bytes
						k++;
					}
					else
					{
						i++;
					}
				}
			}

			if (line[0] == 'E') // Check if the line represents an end record
			{
				printf("Jump to address: %x\n", start); // Print the jump address
				fprintf(out, "Jump to address: %x\n", start); // Print the jump address				
				break;
			}
		} while (!feof(obj)); // Continue reading lines until the end of the file is reached

		fclose(obj); // Close the object file
	}
	else
	{
		printf("Program name does not match!"); // Print an error message if the program name does not match
		fclose(obj);							// Close the object file
	}
}
