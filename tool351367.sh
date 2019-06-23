#!/bin/bash


if [ "$1" == "" ]; then  #an den do8oun orismata epestrepse ta am
echo "1054351-1054367"
nop="true"
fi
dateA=1900  #arxikes times stis hmeromhnies se periptwsh pou den so8ei mia apo autes
dateB=2018
while [ "$1" != "" ]; do  #oso uparxei positional parameter sthn prwth 8esh
  case $1 in
	-f )		shift  #kane shift sta positional parameters pros ta aristera
			filename="$1" #dwse sthn metablhth filename thn timh tou orismatos
			;;
	-id )  		shift
			id="$1"  #dwse sthn metablhth id thn antistoixh timh tou orismatos
			;;
	--firstnames )	names="fnames"  #ane8ese sthn metablhth names  to string fnames
			;;
	--lastnames ) 	names="lnames"  #ane8ese sthn metablhth names  to string lnames
			;;
	--born-since ) 	shift
			dateA="$1" #ane8ese sthn metablhth dateA to antistoixo orisma
			date1="true"
			;;
	--born-until ) shift
			dateB="$1"  #ane8ese sthn metablhth dateB to antistoixo orisma
			date2="true"
			;;
	--socialmedia )	sc="true"  #ane8ese sthn metablhth sc to string true
			;;
	--edit )	shift
			id="$1"  #ane8ese sthn metablhth id to antistoixo orisma
			shift
			col="$1"  #ane8ese sthn metablhth col to antistoixo orisma
			shift
			val="$1"  #ane8ese sthn metablhth val to antistoixo orisma
			edit="true"  #ane8ese sthn metablhth edit to string true
			;;
 esac
 shift  # h $1 den periexei kamia timh
done  #me thn parapanw loop exasfalizoume oti 8a diabastoun ola ta orismata kai den mas endiaferei h seira
# stis awk entoles to !/^#/ exasfalizei oti den 8a agnoountai oi grammes sxolia
# -F orizei ws delimiter to akolou8o sumbolo |

if [ "$nop" != "true" ] #an exei dw8ei toulaxiston ena orisma
then
if [ "$filename" != "" -a  "$names" == "fnames" ] # to -a einai and
then
#firstnames
awk -F "|" '!/^#/ {a[$3]++} END { for (b in a) {print b} }' "$filename" | sort #ftiaxnei ton pinaka a[onoma]  tupwnei tis diakrites times kai kanei sort
elif [ "$filename" != "" -a "$names" == "lnames" ]
then
#lastnames
awk -F "|" '!/^#/ {a[$2]++} END { for (b in a) {print b} }' "$filename" | sort #antistoixa me to parapanw tupwnei diakrita last names
elif [ "$filename" != ""  -a "$id" != ""  -a "$col" != ""  -a "$val" != "" -a "$edit" == "true" ]
then
#edit
awk -F "|" ' {if($1 == "'"$id"'" && "'"$col"'" <= 8 && "'"$col"'" >= 2) {$ "'"$col"'" = "'"$val"'"}{print}}''{OFS= "|"}'  "$filename" > output.txt && mv output.txt "$filename"
#tsekarei an plhrountai oi proipo8eseis ths edit  kanei tis allages kai tis apo8hkeuei sto output.txt kai meta antigrafei to allagmeno arxeio sto arxiko
elif [ "$date1" == "true" -o "$date2" == "true" -a "$filename" != "" ]
then
#dateA  dateB
awk -F "|" '!/^#/ { if($5 >= "'"$dateA"'" && $5 <="'"$dateB"'")  print $0}' "$filename" # tupwnei thn grammh mono ama einai anamesa sta sygkekrimena dates

elif [ "$filename" != "" -a "$id" != "" -a "$edit" == "" ]
then
#id
awk -F "|" ' !/^#/ { if($1 == "'"$id"'")  {print $3,$2,$5}}' "$filename" #tupwnei tis antistoixes sthles gia thn grammh me to zhtoumeno  id
elif [ "$filename" != "" -a "$sc" == "true" ]
then
echo "social"
awk 'BEGIN {FS ="|"; RS="\r\n"}!/^#/ {a[$9]++} END { for (b in a) print b,a[b] }' event.dat| sort #orizoume ws row separator to \r\n epeidh etsi einai orismeno apo ton dhmiourgo tou arxeiou
#to upoloipo kommati pairnei tis diakrites times ths antistoixhs sthlhs me ta social media tupwnei tis diakrites times kai poses fores emfanisthke ka8e mia kai sto telos na kanei sort
else #se periptwsh pou ta orismata allwn entolwn den do8oun swsta 8a  tupw8ei olo to arxeio
#whole file
awk '!/^#/' "$filename" #tupwnetai olo to arxeio(xwris ta sxolia)
fi
fi


