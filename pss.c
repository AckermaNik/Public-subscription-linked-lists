/***************************************************************
 *
 * file: pss.h
 *
 * @Author  Nikolaos Vasilikopoulos (nvasilik@csd.uoc.gr)
 * @Version 20-10-2020
 *
 * @e-mail       hy240-list@csd.uoc.gr
 *
 * @brief   Implementation of the "pss.h" header file for the Public Subscribe System,
 * function definitions
 *
 *
 ***************************************************************
 */
#include <stdio.h>
#include <stdlib.h>

#include "pss.h"

/**
 * @brief Optional function to initialize data structures that
 *        need initialization
 *
 * @return 0 on success
 *         1 on failure
 */

#define MG 64
struct Group G[MG];            /* dimiourgia pinaka ton 64 structs group*/

struct SubInfo* subinfohead; /*dimiourgia head pointer gia subscriptionInfo list*/



int initialize(void){
	 int i;
	 subinfohead=NULL;
     for(i=0;i<MG;i++){
	    G[i].gId=i;            /* number of each team*/

        G[i].gfirst=NULL;      /* initialization of pointers for eatch team*/
        G[i].glast=NULL;
        G[i].ggsub=NULL;


     }
     return EXIT_SUCCESS;
}
/**
 * @brief Free resources
 *
 * @return 0 on success
 *         1 on failure
 */
int free_all(void){
	struct Info* tempi=malloc(sizeof(struct Info));
	struct SubInfo* temps=malloc(sizeof(struct SubInfo));
	struct Subscription* tempggs=malloc(sizeof(struct Subscription));
	int i;
	while(subinfohead!=NULL){        /*katastrofh SubInfo list*/
		temps=subinfohead;
		subinfohead=subinfohead->snext;
		free(temps);
	}
	for(i=0;i<MG;i++){       /* gia kathe mia apo tis omades diagrafh tvn liston tous*/
	  while(G[i].gfirst!=NULL){
       tempi=G[i].gfirst;       /* katastrofi Info list*/
       free(tempi);
       G[i].gfirst=G[i].gfirst->inext;
	  }
	  while(G[i].ggsub!=NULL){ /* katastrofi subscription list*/
	         tempggs=G[i].ggsub;
	         free(tempggs);
	         G[i].ggsub=G[i].ggsub->snext;
	  	 }

	}
    return EXIT_SUCCESS;
}

/**
 * @brief Insert info
 *
 * @param iTM Timestamp of arrival
 * @param iId Identifier of information
 * @param gids_arr Pointer to array containing the gids of the Event.
 * @param size_of_gids_arr Size of gids_arr including -1
 * @return 0 on success
 *          1 on failure
 */
#include <stdio.h>
#include <stdlib.h>


/* OI TAXINOMISEIS GINONTAI ME AUXOUSA SEIRA*/



/*synarthseis gia typo Info lists*/

void insertstart(int iTM,int iId,struct Info** head,struct Info** end,int array[64],int arnum){
	int j;
	struct Info* newnode =malloc(sizeof(struct Info)); /* desmeusei mnimis gia ton neo komvo pou tha ginei insert*/
	if(!newnode){
		 printf("Adunamia desmeuseis mnimis1");
		 exit(1) ;
	}
	newnode->iId=iId;    /*arxikopoihsh ton pedion tou neo komvou */
	newnode->itm = iTM;

	for(j=0;j<64;j++){
	 	 newnode->igp[j]=0;
	  }
	for(j=0;j<arnum-1;j++){
		 newnode->igp[array[j]]=1; /* bazo 1 stis omades pou exoun thn idia plhroforia me aythn*/
	 }
	newnode->inext = *head;   /* NULL thn proth fora*/
	newnode->iprev=NULL;
	(*head)= newnode;        /* o head ginetai o 2os komvos tora*/
	if(*end==NULL){          /* gia thn 1h fora pou tha exo mono ena stoixeio arxika sthn lista*/
	  *end=newnode;
	}
}

void insertend(int iTM,int iId,struct Info** end,int array[64],int arnum){
	struct Info* newnode =malloc(sizeof(struct Info));   /* desmeusei mnimis gia ton neo komvo pou tha ginei insert*/
	int j;
		if(!newnode){
			 printf("Adunamia desmeuseis mnimis1");
			  return ;
		}
		newnode->iId=iId;          /*arxikopoihsh ton pedion tou neo komvou */
		newnode->itm = iTM;
		for(j=0;j<64;j++){
		 	 newnode->igp[j]=0;
		  }
		for(j=0;j<arnum-1;j++){
			 newnode->igp[array[j]]=1;
		 }
		newnode->inext = NULL; /* NULL afou einai o teleutaios komvos*/

		(*end)->inext=newnode;
		newnode->iprev=(*end);
		*end=newnode;          /* o end tora deixnei dto neo teleutaio*/

}

void insertafter(int iTM,int iId,struct Info* prev,int array[64],int arnum){       /* dino ton deikti tou komvou prin apo athn thesi pou thelo na kano insertafter*/
 int j;
 struct Info* after =malloc(sizeof(struct Info));
 struct Info* newnode =malloc(sizeof(struct Info));
 struct Info* prevafter =malloc(sizeof(struct Info));
 if(!after || !newnode || !prevafter){
	printf("Adunamia desmeuseis mnimis2");
		 exit(1) ;
 }

 newnode->iId=iId;     /*arxikopoihsh ton pedion tou neo komvou */
 newnode->itm =iTM;


 for(j=0;j<64;j++){
 	 newnode->igp[j]=0;
  }
 for(j=0;j<arnum-1;j++){
	 newnode->igp[array[j]]=1;
 }

 after = prev->inext;    /* syndesi deikton inext and iprev*/
 prevafter=after->iprev;
 prev->inext= newnode;
 newnode->inext = after;
 newnode->iprev=prev;
 prevafter=newnode;
}

void DL_print(struct Info* head){
	struct  Info* current;
	current=head;

	while(current!=NULL){
		printf("ITM: %d",current->itm);
		printf("  Id: %d",current->iId);
		printf(",  ");
		/*for(int j=0;j<64;j++){
			printf("omada:%d  %d\n",j,current->igp[j]);
		}*/

		current=current->inext;
	}
}
int DL_LookUp(int id,struct Info* head,struct Info* end){ /* metakinino tautoxrona tous pointers ths arxhs kai tou telous gia grigoroteri anazitisi*/
	struct Info* left =malloc(sizeof(struct Info));
	struct Info* right =malloc(sizeof(struct Info));
	if(!left|| !right ){
		printf("Adunamia desmeuseis mnimis1");
		exit(1);
	}

	left=head;
	right=end;
	while( (left!=NULL && right!=NULL)&& (left->iprev)!=right){ /* elegxo na mhn ginei kapoios deiktis NULL kai na mhn xeperasi o right ton left*/
		if((left->iId)==id || (right->iId)==id){
			return 1;   /* vrethike sthn lista*/
		}
		left=left->inext;
		right=right->iprev;
	}
	if(left==NULL && right!=NULL){ /*eidikes periptoseis an kapoios ginei NULL eno o allosoxi opos an h lista exei mono 1 h 2 stoixeia*/
		if((right->iId)==id){
				return 1;
		}
	}
	else if(right==NULL && left!=NULL){
		if((left->iId)==id){

			return 1;
		}
	}

	return 0;

}

void DL_insert(int iTM,int iId,struct Info** head,struct Info** end,int array[64],int arnum){

		struct Info* prev=malloc(sizeof(struct Info));
		struct Info* current=malloc(sizeof(struct Info));
	    if(!prev || !current ){
				 printf("Adunamia desmeuseis mnimis1");
				 exit(1);
		}


		if(*head==NULL){ /* proth fora insert*/
			insertstart(iTM,iId,head,end,array,arnum);

			return;
		}
		else{
			current=*head;
			prev=current;
		}


		 while(current!=NULL){
			if(current==*head && (current->itm)>iTM){
				insertstart(iTM,iId,head,end,array,arnum);
				return;
			}
			else if((current->itm)>iTM){

				insertafter(iTM,iId,prev,array,arnum);

				return;
			}
			prev=current;
			current=current->inext;

		}

		insertend(iTM,iId,end,array,arnum); /* an apla prepei na prostethei sto telos*/

}
void deletestart(int x,struct Info** head,struct Info** end){
	struct Info* newnode =malloc(sizeof(struct Info));
	if(!newnode){
		 printf("Adunamia desmeuseis mnimis1");
		 exit(1) ;
	}
	printf("\nDeleted with id:  %d",x);

	newnode =(*head)->inext; /* diagrathi kai allagh  pointer head*/
	free(*head);
	(*head)= newnode;
	if(*end==*head){ /*an exo mono ena stoixeio mesa*/
	 free(*end);
	}
}

void deleteafter(int x,struct Info* prev){       /* dino ton deikti tou komvou prin apo auton pou thelo na diagrapso*/
 struct Info* after =malloc(sizeof(struct Info));
 struct Info* newnode =malloc(sizeof(struct Info));

 if(!after || !newnode){
	printf("Adunamia desmeuseis mnimis2");
		 exit(1) ;
 }


 printf("\nDeleted with id:  %d",x);

                                    /* syndesi deikton inext kai iprev*/
 after = prev->inext->inext;
 free(prev->inext);
 prev->inext=after;
 after->iprev=prev;
}

void deleteend(int x,struct Info** end){
	struct Info* temp =malloc(sizeof(struct Info));
		if(!temp){
			 printf("Adunamia desmeuseis mnimis1");
			  return ;
		}

		printf("Delete with id:  %d\n",x);

        temp=(*end)->iprev;				 /* syndesi deikton inext kai iprev*/
        free(*end);
        *end=temp;
		(*end)->inext=NULL;

}

void DL_delete(int x,struct Info** head,struct Info** end){ /*deletes according to Id*/
	printf("-------------\n");
		struct Info* prev =malloc(sizeof(struct Info));
		struct Info* current =malloc(sizeof(struct Info));
	    if(!prev || !current ){
				 printf("Adunamia desmeuseis mnimis1");
				 exit(1);
		}



		current=*head;
		prev=current;


		while(current!=NULL){

			if(current==*head && (current->iId)==x){
			   deletestart(x,head,end);
				return;
			}
			else if(current->inext==NULL && (current->iId)==x){
				deleteend(x,end);
				return;
			}
			else if((current->iId)==x){
				deleteafter(x,prev);

			}
			prev=current;
			current=current->inext;

		}

 }


int Insert_Info(int iTM,int iId,int* gids_arr,int size_of_gids_arr){

    int i;
    for(i=0;i<size_of_gids_arr-1;i++){ /* gia tis omades tou gids_arr*/
    	if(!DL_LookUp(iId,G[gids_arr[i]].gfirst,G[gids_arr[i]].glast)){ /* an den yparxei idi ayth h plhroforia se mia omada(idio Id) na eisaxthei*/
    	  DL_insert(iTM,iId,&G[gids_arr[i]].gfirst,&G[gids_arr[i]].glast,gids_arr,size_of_gids_arr);
    	  printf("\nGROUPID=<%d> ",gids_arr[i]);
    	  printf("INFOLIST= ");
    	 /* DL_delete(2,&G[gids_arr[i]].gfirst,&G[gids_arr[i]].glast);*/
    	  DL_print(G[gids_arr[i]].gfirst); /* ektyposei infolist kathe omadas*/
    	 }
    }
    return EXIT_SUCCESS;
}
/**
 * @brief Subsriber Registration
 *
 * @param sTM Timestamp of arrival
 * @param sId Identifier of subscriber
 * @param gids_arr Pointer to array containing the gids of the Event.
 * @param size_of_gids_arr Size of gids_arr including -1
 * @return 0 on success
 *          1 on failure
 */


/* SYNARTHSEIS GIA THN SUBINFO*/




void insertstartsub(int stm,int sid,struct SubInfo** head,int array[64],int arrnum){
	struct SubInfo* newnode =malloc(sizeof(struct SubInfo));
	int i;
	if(!newnode){
		 printf("Adunamia desmeuseis mnimis1");
		  return ;
	}
	newnode->stm = stm;   /* arxikopoihsei ton pedion enos komvou*/
	newnode->sId = sid;
	for(i=0;i<MG;i++){
		newnode->sgp[i]=(struct Info*)1;
	}
	for(i=0;i<arrnum-1;i++){
        newnode->sgp[array[i]]=G[array[i]].gfirst;  /*gia thn kathe omada pou endiaferetai autos o syndromitis kano na deixnei sto proto stoixeio ths Info list ths*/
	}
	newnode->snext = *head; /* NULL*/
	*head = newnode;        /* o head ginetai o 2os komvos tora*/

}



void insertaftersub(int stm,int sid,struct SubInfo* prev,int arr[64],int arrnum){
 struct SubInfo* after =malloc(sizeof(struct SubInfo));
 struct SubInfo* newnode =malloc(sizeof(struct SubInfo));
 int i;
 if(!after || !newnode){
	printf("Adunamia desmeuseis mnimis2");
		 return ;
 }
   newnode->stm = stm;   /* ta idia me thn insert start*/
   newnode->sId = sid;
   for(i=0;i<MG;i++){
 		newnode->sgp[i]=(struct Info*)1;
 	}
 	for(i=0;i<arrnum-1;i++){
         newnode->sgp[arr[i]]=G[arr[i]].gfirst;

 	}
 after = prev->snext; /* syndesi deikton */
 prev->snext = newnode;
 newnode->snext = after;
}

void deletestartsub(int key,struct SubInfo** head) {
	struct SubInfo* temp=malloc(sizeof(struct SubInfo));
	 if(!temp){
		printf("Adunamia desmeuseis mnimis gia temp");
			 return ;
	 }

	temp=(*head)->snext; /* diagrafh tou protoy komvou kai metakinish tou head ston epomeno*/
	printf("\n\nDeleted subscriber:  %d",key);
	free(*head);
	*head = temp;

}


void deleteaftersub(int key,struct SubInfo* prev){   /* o deiktis enos dtoixeiou prin apo ayto pou thelo na diagrapso*/
	struct SubInfo* temp=malloc(sizeof(struct SubInfo));
	 if(!temp){
			printf("Adunamia desmeuseis mnimis gia temp");
				 return ;
		 }

		printf("\n\nDeleted subscriber:  %d",key);

		temp=(prev->snext)->snext; /* katallhlh diagrafh tou prev->next kai syndesi deiktvn*/
		free(prev->snext);
		prev->snext=temp;

}





void SL_insert(int stm,int sid,struct SubInfo** head,int arr[64],int arrnum){

	struct SubInfo* prev =malloc(sizeof(struct SubInfo));
	struct SubInfo* current =malloc(sizeof(struct SubInfo));
    if(!prev || !current ){
			 printf("Adunamia desmeuseis mnimis1");
			 return ;
	}


	if(*head==NULL){  /* gia thn proth eisagvgh komvou*/
		insertstartsub(stm,sid,head,arr,arrnum);

		return;
	}
	else{
		current=*head;
		prev=current;
	}

	while(current!=NULL){
		if(current==*head && (current->stm)>stm){
			insertstartsub(stm,sid,head,arr,arrnum);
			return;
		}
		else if((current->stm)>stm){
			insertaftersub(stm,sid,prev,arr,arrnum);

			return;
		}
		prev=current;
		current=current->snext;

	}

	insertaftersub(stm,sid,prev,arr,arrnum); /* an thelei aplh eisagvgh sto telos ths listas*/


}
void SL_print(struct SubInfo* head){
	struct  SubInfo* current =malloc(sizeof(struct SubInfo));
	current=head;

	while(current!=NULL){  /*emfanisi stoixeion subinbfo*/


		printf("Subscriber with sId:  %d  ",current->sId);
		current=current->snext;
	}


}

void SL_Delete(int key,struct SubInfo** head){
	struct SubInfo* prev =malloc(sizeof(struct SubInfo));
		struct SubInfo* current =malloc(sizeof(struct SubInfo));
	    if(!prev || !current ){
				 printf("Adunamia desmeuseis mnimis1");
				 return ;
		}

	    if(*head==NULL){/* an den yparxoun stoixeiA gia diagrafh*/
	    	return;
	    }

	    current=*head;
	    prev=current;
	    while(current!=NULL){
	    		if(current==*head && (current->sId)==key){
	    			deletestartsub(key,head);
	    			return;
	    		}
	    		else if((current->sId)==key){
	    			deleteaftersub(key,prev);

	    			return;
	    		}
	    		prev=current;
	    		current=current->snext;

	    	}
}



int SL_LookUp(int id,struct SubInfo* head){ /* psaxno an yparxei syndromitis me to sygkekrimeno sId sto systhma*/
	struct SubInfo* current ;
    current=head;

    while(current!=NULL){
    	if((current->sId)==id){

    		return 1;
        }
    	current=current->snext;
    }
    return 0;
}



/* SYNARTHSEIS GIA THN SUBSCRIPTION LIST KATHE OMADAS */



void insertstartsublist(int sid,struct Subscription** head){
	struct Subscription* newnode =malloc(sizeof(struct Subscription));
	if(!newnode){
		 printf("Adunamia desmeuseis mnimis1");
		  return ;
	}

	newnode->sId = sid;
	newnode->snext = *head; /* NULL sthn arxi*/
	*head = newnode;        /* o head ginetai o 2os komvos tora*/

}



void insertaftersublist(int sid,struct Subscription* prev){
 struct Subscription* after =malloc(sizeof(struct Subscription));
 struct Subscription* newnode =malloc(sizeof(struct Subscription));
 if(!after || !newnode){
	printf("Adunamia desmeuseis mnimis2");
		 return ;
 }

 newnode->sId = sid; /* arxikopoihsh pedivn ths*/

 after= prev->snext;  /* syndesi deiktvn*/
 prev->snext = newnode;
 newnode->snext = after;

}

void deletestartsublist(int key,struct Subscription** head) {
	struct Subscription* temp=malloc(sizeof(struct Subscription));
	 if(!temp){
		printf("Adunamia desmeuseis mnimis gia temp");
			 return ;
	 }

	temp=(*head)->snext; /* diagrafh kai allagh head pointer*/
	free(*head);
	*head = temp;

}


void deleteaftersublist(int key,struct Subscription* prev){   /* o deiktis enos dtoixeiou prin apo ayto pou thelo na diagrapso*/
	struct Subscription* temp=malloc(sizeof(struct Subscription));
	 if(!temp){
			printf("Adunamia desmeuseis mnimis gia temp");
				 return ;
		 }


		temp=(prev->snext)->snext; /* diagrafh komvou kai allagh pointer*/
		free(prev->snext);
		prev->snext=temp;

}





void L_insert(int sid,struct Subscription** head){

	struct Subscription* prev =malloc(sizeof(struct Subscription));
	struct Subscription* current =malloc(sizeof(struct Subscription));
    if(!prev || !current ){
			 printf("Adunamia desmeuseis mnimis1");
			 return ;
	}


	if(*head==NULL){  /* prvth fora insert*/

		insertstartsublist(sid,head);
		return;
	}

	current=*head;
	prev=current;

	while(current!=NULL){
		if(current==*head && (current->sId)>sid){
			insertstartsublist(sid,head);
			return;
		}
		else if((current->sId)>sid){
			insertaftersublist(sid,prev);


			return;
		}
		prev=current;
		current=current->snext;

	}

	insertaftersublist(sid,prev); /* aplo insert sto telos ths*/



}


int L_LookUp(int id,struct Subscription* head){ /* psaxno an yparxei o syndromiths me to sygkekrimeno sId sthn subscription list mias omadas*/
	struct Subscription* current ;
    current=head;

    while(current!=NULL){
    	if((current->sId)==id){

    		return 1;
        }
    	current=current->snext;
    }
    return 0;
}



void L_Delete(int key,struct Subscription** head){
	struct Subscription* prev =malloc(sizeof(struct Subscription));
		struct Subscription* current =malloc(sizeof(struct Subscription));
	    if(!prev || !current ){
				 printf("Adunamia desmeuseis mnimis1");
				 return ;
		}
	    if(*head==NULL){ /* an einai adeia h lista */
	    	return;
	    }

	    current=*head;
	    prev=current;
	    while(current!=NULL){
	    		if(current==*head && (current->sId)==key){
	    			deletestartsublist(key,head);
	    			return;
	    		}
	    		else if((current->sId)==key){
	    			deleteaftersublist(key,prev);

	    			return;
	    		}
	    		prev=current;
	    		current=current->snext;

	    	}

}

void L_print(int* subarr ,int size){
	struct  Subscription* current =malloc(sizeof(struct Subscription));
        int i;
		for(i=0;i<size-1;i++){
			current=G[subarr[i]].ggsub;/* head pointer ths ekastote subscription list*/
			if(current!=NULL){
			printf("\nGROUPID=<%d>  ",subarr[i]);  /*ektiponei ola ta groups exomtas h oxi syndromiti  syndromiti*/
			}
			else{
				printf("\nGROUPID=<%d>  No Subscriber",subarr[i]);
			}
			while(current!=NULL){
		       printf("Subscriber with sId:%d  ",current->sId);
		       current=current->snext;
		    }
	    }
}



int Subscriber_Registration(int sTM,int sId,int* gids_arr,int size_of_gids_arr){
	struct  Subscription* current =malloc(sizeof(struct Subscription));  /*den xero giati alla mono me auto  kai ta parakato akyra inserts mou douleue gia thn for parolo pou exo dokimasei oles tis insert kai einai sostes*/
	int i;
	current =NULL;
    L_insert(8,&current);                 /* ayta einai ta akyra inserts*/
   	L_insert(4,&current);
   	L_insert(5,&current);

     if(!SL_LookUp(sId,subinfohead)){ /* an den yparxei hdh subscriber me idio sId*/
	      SL_insert(sTM,sId,&subinfohead,gids_arr,size_of_gids_arr);

         for(i=0;i<size_of_gids_arr-1;i++){

	       L_insert(sId,&G[gids_arr[i]].ggsub);

         }

     printf("\n");
     printf("-----------------------------------------------");
     printf("\nSUBSCRIBERSINFO LIST: \n");
     SL_print(subinfohead); /* ektyposh ths SubInfo*/

     L_print(gids_arr,size_of_gids_arr); /* ektyposh ths subscription list kathe omadas*/
     }
    return EXIT_SUCCESS;
}
/**
 * @brief Consume Information for subscriber
 *
 * @param sId Subscriber identifier
 * @return 0 on success
 *          1 on failure
 */
int Consume(int sId){
	struct  SubInfo* current =malloc(sizeof(struct SubInfo));
	struct Info* temphead= malloc(sizeof(struct Info));
	int i;

	current= subinfohead;
    if(SL_LookUp(sId,subinfohead)){ /* elegxo arxika an yparxei autos o subscriber*/
    	while(current!=NULL && current->sId!=sId){
    		current=current->snext; /* euresi komvou me ayto to sid sthn SubInfo*/
    	}

    	for(i=0;i<MG;i++){
    		if(current->sgp[i]==NULL){ /* ksanatsekaro mhn exei isaxtjhei kanena stoixeio stous proigoumenes NULL Info lists gia tis omades pou endiaferotan o ekastote syndromitis*/
    			current->sgp[i]=G[i].gfirst; /* an pleon den einai NULL ton ananeono katallhla vazontas to stoixeio you pinaka na deixnei ston head pointer ths omadas pou tvea omvs den einai NULL*/
    		}

    	}
        for(i=0;i<MG;i++){
        	if(current->sgp[i]!=(struct Info*)1 && current->sgp[i]!=NULL){ /* an eimai se omada pou endiaferei ton syndromiti kai h opoia exei kai plhrofories*/
                 temphead=current->sgp[i];

                 while(temphead->inext!=NULL){ /* pao sthn teleutaia plhroforia*/
                	 temphead=temphead->inext;
                 }

                 printf("\n\nConsume event for subscriber with id:%d\n",sId);
                 printf("GROUPID=<%d>",i);
                 printf(" ,INFOLIST= ");
                 DL_print(current->sgp[i]);


                 current->sgp[i]=temphead; //o  pointer tou pinaka deixnei tora sthn pio prosfati pliroforia*/
                 printf("NEWSGP= %d",current->sgp[i]->iId);


        	}

        	}
        }


    return EXIT_SUCCESS;
}
/**
 * @brief Delete subscriber
 *
 * @param sId Subscriber identifier
 * @return 0 on success
 *          1 on failure
 */
int Delete_Subscriber(int sId){
	int i;
	struct  Subscription* current =malloc(sizeof(struct Subscription));
	if(SL_LookUp(sId,subinfohead)){     /* vlepo arxika an yparxei autos o subscriber*/
		SL_Delete(sId,&subinfohead);    /* ton kano delete*/
		printf("\n");

		printf("NEW SUBSCRIBERSINFO LIST:\n");
		SL_print(subinfohead);

		for(i=0;i<MG;i++){
			if(L_LookUp(sId,G[i].ggsub)){ /* arxika vlepo an sthn sublist ayths ths omadas yparxei o subscriber pou thelo na diagrapso*/
			L_Delete(sId,&G[i].ggsub);

			current= G[i].ggsub; /* gia thn ektypvsh ths sublist ths omadas*/

			if(current!=NULL){       /* ayth h if xrisimeuei sto na typono ta katallhla mhnymata mono */
				        printf("\n");
						printf("GROUPID=<%d>  ",i);  /*ektiponei ola ta groups pou exoun esto kai ena syndromiti*/
						printf("NEW SUBLIST:  ");
			}
			else{
				printf("\nGROUPID<%d>    No Subscriber",i);/*ektiponei kai thn pliroforia oti h omada ayth den exei subscriber an den exei kanenan*/
			}



			while(current!=NULL){   /* ektuposh ths subscription list kathe omadas*/
			    printf("Subscriber with sId:%d  ",current->sId);
				current=current->snext;
		    }
            printf("\n");
		    }
		}

	}
    return EXIT_SUCCESS;
}
/**
 * @brief Print Data Structures of the system
 *
 * @return 0 on success
 *          1 on failure
 */
int Print_all(void){
	int omades=0,subs=0,i;
	struct  Subscription* current =malloc(sizeof(struct Subscription));
	struct  SubInfo* currentsubinfo =malloc(sizeof(struct SubInfo));
	printf("\n\n----------------------PRINT ALL----------------------\n");

	for(i=0;i<MG;i++){ /* gia kathe omada*/
		printf("\nGROUPID=<%d> ",i);

		if(G[i].gfirst!=NULL){ /*NO GROUPS= omades pou exoun plhrofories*/
		     omades++;
		     printf(" ,INFOLIST= ");
		     DL_print(G[i].gfirst);


		     if(G[i].ggsub!=NULL){ /* gia katallhlo typoma mhnymatos*/
		      printf(" SUBLIST= ");
		     }
		     else{
		    	 printf(" SUBLIST= NO SUBSCRIBERS ");
		     }
		}
		else{
			printf("NO INFOS\n");
		}

		current=G[i].ggsub;
		while(current!=NULL){   /* ektuposh ths subscription list kathe omadas*/

			printf("Subscriber with sId:%d  ",current->sId);
			 current=current->snext;
		 }
	}

	printf("\nSUBSCRIBERLIST=  ");  /* ektypvsh  ths SubInfo list*/
	SL_print(subinfohead);

    currentsubinfo=subinfohead;
    while(currentsubinfo!=NULL){    /*emfanisi id omadvn pou endiaferetai kathe subscriber*/

    	subs++; /* NO_SUBSCRIBERS*/

         printf(" \nSUBSCRIBERID<%d>  ",currentsubinfo->sId);
		 printf(" GROUPID=<");
		 for(i=0;i<MG;i++){
			if(currentsubinfo->sgp[i]!=(struct Info*)1){
				printf("%d,",i);
			}
		}
        printf(">");
		currentsubinfo=currentsubinfo->snext;
	}
    printf("\nNO_GROUPS=<%d>, NO_SUBSCRIBERS=<%d>",omades,subs);



    return EXIT_SUCCESS;
}
