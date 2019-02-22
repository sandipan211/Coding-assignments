#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <strings.h>
#include <math.h>

#define prompt "myfs>"
#define max_datablocks_per_inode 50
#define bufsize 1024
#define ibmsize 1024
#define dbmsize 1024*1024
#define max_no_of_drives 10
#define fsize 20
#define pathsize 300
#define path "/home/sandipan/Academics/semester_6/Operating_systems/"


void createFS(char subc[][20]);
void listFS(char subc[][20]);
void mountFS(char subc[][20]);
void copyfn(char subc[][20]);
int mkfile(char subc[][20]);
int find_free_inode(char []);
int find_free_db(char []);
void rmfile(char subc [][20]);
void movefile(char subc[][20]);
void showFS();

typedef struct superblock
{
	long fssize;
	int blocksize;
	int inode_size;
	int root_node_no;
	int inode_start_loc;
	int block_start_loc;
	int inode_count;
	int blockcount;
	int free_inode_count;
	long free_block_count;
	unsigned char ibm[ibmsize];
	unsigned char dbm[dbmsize];

}sb;


typedef struct mount
{
	char drive_name[5];
	int ismounted;
	char fsname[fsize];
}use;
use drive[max_no_of_drives];

typedef struct i_node
{
	char fname[fsize];
	char type;
	int size;	
	int datablock_count;
	int datablocks[max_datablocks_per_inode];

}inode;


#define in_size (sizeof(inode))
#define sbsize (sizeof(sb))

int drivenum = 0;
char cwd[300];
char hostname[300];
char username[300];

int main()
{
	int loop = 1;
	char command[bufsize];
	char parsedstr[5][20];
	int i,s, j,ctr;

	getcwd(cwd,sizeof(cwd));
	gethostname(hostname, 300);
	getlogin_r(username, 300);

	do
	{

	bzero(command, bufsize);
	for(i=0;i<5;i++)
		bzero(parsedstr[i], 20);
	
	printf("\nsandipan@%s:~%s: %s ", hostname, cwd, prompt);
	
	// printf("\ncommand1 = %s", command);
	if(fgets(command, sizeof(command),stdin)==NULL)
		perror("fgets out");
	command[strcspn(command,"\n")]= '\0';
		// printf("\ncommand2 = %s", command);

	j=0; ctr=0;
    for(i=0;i<=(strlen(command));i++)
    {
        // if space or NULL found, assign NULL into parsedstr
        if(command[i]==' '||command[i]=='\0')
        {
            parsedstr[ctr][j]='\0';
            ctr++;  //for next word
            j=0;    //for next word, init index to 0
        }
        else
        {
            parsedstr[ctr][j]=command[i];
            j++;
        }
    }

    if(strcmp(parsedstr[0],"mkfs")==0)
    {
    	createFS(parsedstr);
    }
    else if(strcmp(parsedstr[0],"show")==0)
    {
    	showFS();
    }
    else if(strcmp(parsedstr[0],"ls")==0)
    {
    	listFS(parsedstr);
    }
    else if(strcmp(parsedstr[0],"use")==0) 
    {
    	mountFS(parsedstr);
    }
    else if(strcmp(parsedstr[0],"cp")==0) 
    {
    	copyfn(parsedstr);
    }
    else if(strcmp(parsedstr[0], "mkfile")==0)
    {
    	int retval;
    	
    	retval = mkfile(parsedstr);
    	if(retval==-1)
    		printf("\nERROR!");
    	else
    		printf("\nFile created successfully!");

    }
    else if (strcmp(parsedstr[0], "rm")==0)
    {
    	rmfile(parsedstr);
    }
    else if(strcmp(parsedstr[0], "mv")==0)
    {
    	movefile(parsedstr);
    }
    else if(strcmp(parsedstr[0], "help")==0)
    {
    	printf("\nAvailable commands\n_____________________________");
    	printf("\n1.mkfs\n2.mkfile\n3.use\n4.cp\n5.mv\n6.rm\n7.ls\n8.show\n9.help\n10.exit\n");
    }
    else if(strcmp(parsedstr[0], "exit")==0)
    	exit(0);
    // printf("loop again? (1 for yes and 0 for no)");
    // scanf(" %d",&loop);
    // getchar();

	} while(1);
}


void createFS(char sc[][20])
{
	long osfsize;
	int i,n, fdesc;
	inode node;
	sb sblk;
	char number[10], pathname[pathsize];
	sb wbuf;

	for(i=0;i<20;i++)
	{
		if(isdigit(sc[3][i])!=0)
			number[i] = sc[3][i];
		else
			break;
	}

	osfsize = (atoi(number))*1048576;
	bzero(pathname, pathsize);
	strcpy(pathname, path);
	strcat(pathname, sc[1]);
	fdesc = open(pathname,O_RDWR|O_CREAT,S_IRWXU);
	
	/* initializing superblock */
	sblk.fssize = osfsize;
	sblk.blocksize = atoi(sc[2]);
	sblk.root_node_no = 0;
	sblk.inode_size = in_size;
	sblk.inode_start_loc = sbsize;
	sblk.inode_count = (0.1*osfsize)/in_size;
	sblk.block_start_loc = (long)(sbsize+in_size*sblk.inode_count);
	sblk.blockcount = (long)((osfsize-sblk.block_start_loc)/sblk.blocksize);
	sblk.free_block_count = sblk.blockcount;
	sblk.free_inode_count = sblk.inode_count;
	for(i=0;i<ibmsize;i++)
		sblk.ibm[i] = 0;

	for(i=0;i<dbmsize;i++)
		sblk.dbm[i] = 0;

	/* create root folder */
	sblk.free_inode_count--;
	node.type = 'd';
	bzero(node.fname, fsize);
	strcpy(node.fname, "root");
	node.size = 0;
	node.datablock_count = 0;
	sblk.ibm[0] = 128;
	sblk.dbm[0] = 128;

	for(i=0;i<max_datablocks_per_inode;i++)
		node.datablocks[i] = -1;		//-1 indicates that no info of any datablock is currently stored
	
	lseek(fdesc,0,SEEK_SET);
	long s;
	write(fdesc,&sblk,sbsize);
	lseek(fdesc,sbsize,SEEK_SET);
	write(fdesc, &node, in_size);
	lseek(fdesc,0,SEEK_SET);
	s = read(fdesc,&wbuf,sbsize);


	ftruncate(fdesc, osfsize);
	// close(fdesc);
}

void mountFS(char sc[][20])
{
	strcpy(drive[drivenum].fsname,sc[1]);
	strcpy(drive[drivenum].drive_name,sc[3]);
	drive[drivenum].ismounted = 1;
	drivenum++;
}


void copyfn(char sc[][20])											// format: cp C:testfile1 D:testfile2 
{
	inode node;
	sb sblk;
	int i, j, fd, fd2;
	char d1name[5], d2name[5], f1name[fsize], f2name[fsize], pathname[pathsize];
	
	bzero(d1name, 5);
	bzero(d2name, 5);
	bzero(f1name, fsize);
	bzero(f2name, fsize);

	memcpy(d1name, sc[1], 2);
	strcpy(f1name, sc[1]+2);
	memcpy(d2name, sc[2], 2);
	strcpy(f2name, sc[2]+2);

	for(i=0;i<max_no_of_drives;i++)
	{
		if(strcmp(drive[i].drive_name,d1name)==0)
			break;
	}
	if(i==max_no_of_drives)
	{
		printf("\nNo such drive name as %s", d1name);
		return;
	}


	for(j=0;j<max_no_of_drives;j++)
	{
		if(strcmp(drive[j].drive_name,d2name)==0)
			break;
	}
	if(j==max_no_of_drives)
	{
		printf("\nNo such drive name as %s", d2name);
		return;
	}

	bzero(pathname, pathsize);
	strcpy(pathname, path);
	strcat(pathname,drive[i].fsname);
	fd = open(pathname, O_RDWR,S_IRWXU);
	lseek(fd, 0, SEEK_SET);
	read(fd, &sblk, sbsize);
	lseek(fd, sbsize, SEEK_SET);


	int ibmcount = 0;
	int shift = 7;
	int check;

	for(i=1;i<=sblk.inode_count;i++)
	{
		check = sblk.ibm[ibmcount] & (1<<shift);
		check = check/(int)pow(2,shift);
		shift--;

		if(check==1)
		{
			read(fd, &node, in_size);
			if(strcmp(node.fname,f1name)==0)
			{
				break;
			}
		}
		
		if(shift<0)
		{
			shift = 7;
			ibmcount++;
		}
		lseek(fd, sbsize+in_size*i, SEEK_SET);
	}


	if(i>sblk.inode_count)
	{
		printf("\nNo such file as %s in drive %s! Cannot copy!", f1name, d1name);
		return;
	}

	char makefilestr[4][20];
	int numchars; //n. of characters in size including null character
	inode dest_node;
	sb dest_sb;
	numchars = (int)((ceil(log10(node.size))+1)*sizeof(char));
	char characters[numchars];
	sprintf(characters, "%d", node.size);
	strcpy(makefilestr[0], "mkfile");
	strcpy(makefilestr[1], sc[2]);
	strcpy(makefilestr[2], "notnew");
	strcpy(makefilestr[3], characters);

	char buffer[node.size];
	bzero(buffer, sizeof(buffer));
	int freenode, k;
	freenode = mkfile(makefilestr);


	for(k=0;k<node.datablock_count;k++)
	{
		lseek(fd, sblk.block_start_loc+sblk.blocksize*(node.datablocks[k]-1), SEEK_SET);
		read(fd, &buffer+k*sblk.blocksize, sblk.blocksize);		//can be errors?!?!
	}
	  
	

	bzero(pathname, pathsize);
	strcpy(pathname, path);
	strcat(pathname,drive[j].fsname);

	fd2 = open(pathname, O_RDWR,S_IRWXU);

	int bnum, dbmno;
	lseek(fd2, 0, SEEK_SET);
	read(fd2, &dest_sb, sbsize);
	lseek(fd2, dest_sb.inode_start_loc+in_size*(freenode-1), SEEK_SET);
	read(fd2, &dest_node, in_size);

	for(j=0;j<dest_node.datablock_count;j++)
	{
		bnum = find_free_db(d2name);
		dbmno = bnum/8;
		dest_sb.dbm[dbmno] = dest_sb.dbm[dbmno]|(1<<(8-(bnum%8)));
		dest_sb.free_block_count--;
		dest_node.datablocks[j] = bnum;


		lseek(fd2, dest_sb.block_start_loc+dest_sb.blocksize*(bnum-1), SEEK_SET);
		write(fd2, &buffer+j*dest_sb.blocksize, dest_sb.blocksize);		//can be errors?!?!

	}

	printf("\nFile %s successfully copied from %s to %s as %s", f1name, d1name, d2name, f2name);
}

int mkfile(char sc[][20])
{
	inode node;
	sb sblk;			//sc[0] = mkfile, sc[1] = C:testfile1, sc[2] = new, sc[3] = size
	int i, j, fd, extfd;;
	char dname[5], filename[fsize], pathname[pathsize], filepath[pathsize];
	
	bzero(pathname, pathsize);
	bzero(filepath, pathsize);
	bzero(dname, 5);
	bzero(filename, fsize);

	memcpy(dname, sc[1], 2);
	strcpy(filename, sc[1]+2);

	for(i=0;i<max_no_of_drives;i++)
	{
		if((strcmp(drive[i].drive_name,dname)==0)&&(drive[i].ismounted==1))
			break;
	}
	if(i==max_no_of_drives)
	{
		printf("\nNo such drive name as %s/ This drive is not mounted", dname);
		return -1;
	}

	strcpy(pathname, path);
	strcat(pathname,drive[i].fsname);
	
	fd = open(pathname, O_RDWR,S_IRWXU);
	lseek(fd, 0, SEEK_SET);
	read(fd, &sblk, sbsize);

	if(atoi(sc[3])>(max_datablocks_per_inode*sblk.blocksize))
	{
		printf("\nSize of file exceeded limit! Cannot be more than %d bytes", max_datablocks_per_inode*sblk.blocksize);
		return -1;
	}


	sblk.free_inode_count--;
	node.type = 'f';
	bzero(node.fname, fsize);
	strcpy(node.fname, filename);
	node.size = atoi(sc[3]);
	node.datablock_count = node.size/sblk.blocksize;

	char name[fsize];
	bzero(name, fsize);
	int s;
	if(strcmp(sc[2], "new")==0)
	{
		
		strcpy(filepath, path);
		strcat(filepath, "textfiles/");
		printf("\nEnter source file name: ");
		if(fgets(name, sizeof(name), stdin)==NULL)
			perror("fgets ");
		name[strcspn(name,"\n")]= '\0';

		strcat(filepath, name);
		int bnum, dbmno;
		char buf[sblk.blocksize];

		extfd = open(filepath, O_RDWR,S_IRWXU);
		if(extfd==-1)
			perror("no such file");

		for(j=0;j<node.datablock_count;j++)
		{
			bzero(buf, sblk.blocksize);
			bnum = find_free_db(dname);
			dbmno = bnum/8;
			sblk.dbm[dbmno] = sblk.dbm[dbmno]|(1<<(8-(bnum%8)));
			sblk.free_block_count--;
			node.datablocks[j] = bnum;


			lseek(extfd, sblk.blocksize*j, SEEK_SET);
			read(extfd, &buf, sblk.blocksize);
			lseek(fd, sblk.block_start_loc+sblk.blocksize*(bnum-1), SEEK_SET);
			write(fd, &buf, sblk.blocksize);		

		}


	}




	
	int inum, ibmno;
	inum = find_free_inode(dname);
	ibmno = inum/8;
	sblk.ibm[ibmno] = sblk.ibm[ibmno]|(1<<(8-(inum%8)));
	lseek(fd, 0, SEEK_SET);
	write(fd,&sblk,sbsize);
	lseek(fd, sblk.inode_start_loc+in_size*(inum-1), SEEK_SET);
	write(fd, &node, in_size);

	// close(fd);
	// close(extfd);

	return inum;
}

void listFS(char sc[][20])
{
	inode node;									// sc[0] = ls, sc[1] = C:
	sb sblk;
	int i, fd, filled;	
	char dname[5], pathname[pathsize];

	bzero(dname, 5);
	bzero(pathname, pathsize);

	memcpy(dname, sc[1], 2);

	for(i=0;i<max_no_of_drives;i++)
	{
		if((strcmp(drive[i].drive_name,dname)==0)&&(drive[i].ismounted==1))
			break;
	}
	if(i==max_no_of_drives)
	{
		printf("\nNo such drive name as %s/ This drive is not mounted", dname);
		return;
	}
	strcpy(pathname, path);
	strcat(pathname, drive[i].fsname);		

	fd = open(pathname, O_RDWR,S_IRWXU);
	lseek(fd, 0, SEEK_SET);
	read(fd, &sblk, sbsize);	

	lseek(fd, sbsize, SEEK_SET);

	int ibmcount = 0;
	int shift = 7;
	int check;

	for(i=1;i<=sblk.inode_count;i++)
	{
		check = sblk.ibm[ibmcount] & (1<<shift);
		check = check/(int)pow(2,shift);
		shift--;

		if(check==1)
		{
			read(fd, &node, in_size);
			printf("\n%s..................%d", node.fname, node.size);
		}
		
		if(shift<0)
		{
			shift = 7;
			ibmcount++;
		}
		lseek(fd, sbsize+in_size*i, SEEK_SET);
	}

	// close(fd);
}


int find_free_inode(char dname[])
{
	sb sblk;
	inode node;
	int i, fd, inodenum = 0;
	int count, temp, pos = 0;
	char pathname[pathsize];

	for(i=0;i<max_no_of_drives;i++)
	{
		if((strcmp(drive[i].drive_name,dname)==0)&&(drive[i].ismounted==1))
			break;
	}
	if(i==max_no_of_drives)
	{
		printf("\nNo such drive name as %s/ This drive is not mounted", dname);
		return -1;
	}

	bzero(pathname, pathsize);
	strcpy(pathname, path);
	strcat(pathname, drive[i].fsname);		

	fd = open(pathname, O_RDWR,S_IRWXU);

	lseek(fd, 0, SEEK_SET);
	read(fd, &sblk, sbsize);

	for(i=0;i<ibmsize;i++)
	{
		if(sblk.ibm[i]!=255)
		{
			for (temp=sblk.ibm[i], count=0; temp>0; temp>>=1, count++)
				if ((temp & 1) == 0) 
					pos = count; 
			pos = 8-pos;
			inodenum += pos;
			break;
		}
		else
			inodenum +=  8;

	}

	// close(fd);
	return inodenum;

}

int find_free_db(char dname[])
{
	sb sblk;
	inode node;
	int i, fd, bnum = 0;
	int count, temp, pos = 0;
	char pathname[pathsize];

	for(i=0;i<max_no_of_drives;i++)
	{
		if((strcmp(drive[i].drive_name,dname)==0)&&(drive[i].ismounted==1))
			break;
	}
	if(i==max_no_of_drives)
	{
		printf("\nNo such drive name as %s/ This drive is not mounted", dname);
		return -1;
	}

	bzero(pathname, pathsize);
	strcpy(pathname, path);
	strcat(pathname, drive[i].fsname);		

	fd = open(pathname, O_RDWR,S_IRWXU);

	lseek(fd, 0, SEEK_SET);
	read(fd, &sblk, sbsize);

	for(i=0;i<dbmsize;i++)
	{
		if(sblk.dbm[i]!=255)
		{
			for (temp=sblk.dbm[i], count=0; temp>0; temp>>=1, count++)
				if ((temp & 1) == 0) 
					pos = count; 
			pos = 8-pos;
			bnum += pos;
			break;
		}
		else
			bnum +=  8;

	}

	// close(fd);
	return bnum;

}

void rmfile(char sc[][20])			//format: rm C:testfile1
{
	sb sblk;
	inode node;

	int i, j, fd;
	char dname[5], fname[fsize], pathname[pathsize];
	
	bzero(dname, 5);
	bzero(fname, fsize);

	memcpy(dname, sc[1], 2);
	strcpy(fname, sc[1]+2);


	for(i=0;i<max_no_of_drives;i++)
	{
		if(strcmp(drive[i].drive_name,dname)==0)
			break;
	}
	if(i==max_no_of_drives)
	{
		printf("\nNo such drive name as %s", dname);
		return;
	}

	bzero(pathname, pathsize);
	strcpy(pathname, path);
	strcat(pathname, drive[i].fsname);		

	fd = open(pathname, O_RDWR,S_IRWXU);

	int ibmcount = 0;
	int shift = 7;
	int check, bnum, dbmno;

	lseek(fd, 0, SEEK_SET);
	read(fd, &sblk, sbsize);
	lseek(fd, sbsize, SEEK_SET);

	for(i=1;i<=sblk.inode_count;i++)
	{
		check = sblk.ibm[ibmcount] & (1<<shift);
		check = check/(int)pow(2,shift);
		shift--;

		if(check==1)
		{
			read(fd, &node, in_size);
			if(strcmp(node.fname,fname)==0)
			{
				break;
			}
		}
		
		if(shift<0)
		{
			shift = 7;
			ibmcount++;
		}
		lseek(fd, sbsize+in_size*i, SEEK_SET);
	}

	if(i>sblk.inode_count)
	{
		printf("\nNo such file in drive %s! Cannot remove!", dname);
		return;
	}

	for(j=0;j<node.datablock_count;j++)
	{
		bnum = node.datablocks[j];
		dbmno = bnum/8;
		sblk.dbm[dbmno] = sblk.dbm[dbmno]^ (1 << (8-(bnum%8)));
		
		sblk.free_block_count++;
		node.datablocks[j] = -1;
		
	}
	sblk.ibm[ibmcount] = sblk.ibm[ibmcount]^ (1 << (8-(i%8)));
	sblk.free_inode_count++;

	lseek(fd, 0, SEEK_SET);
	write(fd,&sblk,sbsize);
	printf("\nFile %s removed from drive %s!", fname, dname);

}
void movefile(char sc[][20])		// format: mv D:testfile1 D:testfile1a
{
	inode node;
	sb sblk;			
	int i, j, fd1, fd2;
	char d1name[5], d2name[5], f1name[fsize], f2name[fsize], pathname[pathsize];
	
	bzero(pathname, pathsize);
	bzero(d1name, 5);
	bzero(f1name, fsize);
	bzero(d2name, 5);
	bzero(f2name, fsize);

	memcpy(d1name, sc[1], 2);
	strcpy(f1name, sc[1]+2);
	memcpy(d2name, sc[2], 2);
	strcpy(f2name, sc[2]+2);

	for(i=0;i<max_no_of_drives;i++)
	{
		if((strcmp(drive[i].drive_name,d1name)==0)&&(drive[i].ismounted==1))
			break;
	}
	if(i==max_no_of_drives)
	{
		printf("\nNo such drive name as %s/ This drive is not mounted", d1name);
		return;
	}

	for(j=0;j<max_no_of_drives;j++)
	{
		if((strcmp(drive[j].drive_name,d2name)==0)&&(drive[j].ismounted==1))
			break;
	}
	if(j==max_no_of_drives)
	{
		printf("\nNo such drive name as %s/ This drive is not mounted", d2name);
		return;
	}

	strcpy(pathname, path);
	strcat(pathname,drive[i].fsname);
	
	fd1 = open(pathname, O_RDWR,S_IRWXU);
	lseek(fd1, 0, SEEK_SET);
	read(fd1, &sblk, sbsize);
	lseek(fd1, sbsize, SEEK_SET);

	if(strcmp(d1name, d2name)==0)
	{
		int ibmcount = 0;
		int check, shift = 7;
		
		for(i=1;i<=sblk.inode_count;i++)
		{
			check = sblk.ibm[ibmcount] & (1<<shift);
			check = check/(int)pow(2,shift);
			shift--;

			if(check==1)
			{
				read(fd1, &node, in_size);
				if(strcmp(node.fname,f1name)==0)
				{
					strcpy(node.fname, f2name);
					lseek(fd1, sbsize+in_size*(i-1), SEEK_SET);
					write(fd1, &node, in_size);
					printf("\nFile renamed!");
					return;
				}
			}
			
			if(shift<0)
			{
				shift = 7;
				ibmcount++;
			}
			lseek(fd1, sbsize+in_size*i, SEEK_SET);
		}

	}

	char copystr[3][20], rmstr[2][20];
	
	strcpy(copystr[0], "cp");
	strcpy(copystr[1], sc[1]);
	strcpy(copystr[2], sc[2]);

	strcpy(rmstr[0], "rm");
	strcpy(rmstr[1], sc[1]);

	copyfn(copystr);
	rmfile(rmstr);
	printf("\nFile moved successfully!");
}

void showFS()
{
	int i;
	for(i = 0;i<max_no_of_drives;i++)
		if(drive[i].ismounted==1)
			printf("DRIVE LETTER: %s \t\t FILE SYSTEM: %s \t\t MOUNTED: %d\n",drive[i].drive_name, drive[i].fsname, drive[i].ismounted);	
}
