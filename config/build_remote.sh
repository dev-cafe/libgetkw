#!/bin/sh
#
# Script to copy, initialize and build a source repository
# on a remote host. It relies on the following tools:
# git, sha1sum and ssh
#
# Writen by Jonas Juselius <jonas.juselius@uit.no> 
#   University of Tromsø, October 2009
#
# TODO: Plenty

set -e

usage() {
	echo "build_remote.sh {host} {remote_dir} [init]"
	exit 1
}

check_sha1sum() {
	if [ `which sha1sum` ]; then
		sha1sum=`which sha1sum`
	elif [ `which gsha1sum` ]; then
		sha1sum=`which gsha1sum`
	else
		echo "sha1sum missing"
		exit 1
	fi
} 

init_remote() {
	scp $1 stallo:$remote_dir
	ssh $host "set -e;\
	cd $remote_dir; \
	[ -d $dist_dir ] && rm -rf $dist_dir; \
	tar vfxz $1; \
	cd $dist_dir; \
	./setup"
}

distribute() {
	scp $1 stallo:$remote_dir
	ssh $host "set -e;\
	cd $remote_dir/$dist_dir; \
	tar vfxz ../$1;" 
}

build() {
	ssh $host "set -e;\
	cd $remote_dir/$dist_dir/Debug; \
	make all"
}

update_checksums() {
	[ -f $1 ] && rm -f $1
	for i in `git ls-files`; do
		[ -f $i ] && $sha1sum $i >> $1
	done
}

list_changed_files() {
	if [ ! -f $1 ]; then
		echo "Checksums missing in: $1. Updating." 1>&2
		update_checksums $1
		for i in  `git ls-files`; do
			[ ! -d $i ] && echo $i
		done
	else
		failed=`$sha1sum -c $1 2>/dev/null |grep -i FAILED`
		failed=`echo $failed | sed 's/: *FAILED/ /g'`
		for i in $failed; do
			echo $i
		done
	fi
}

gen_archive() {
	[ -f $1 ] && rm -f $1
	for i in `list_changed_files $2`; do
		tar vfu $1 $i
	done
}


check_sha1sum

host=$1
remote_dir=$2
init=$3

[ "x$host" = "x" ] && usage
[ "x$remote_dir" = "x" ] && usage

dist_name="mrchem2"
dist_file="mrchem2-dev.tar"
dist_dir="mrchem2-dev"

remote_dir_name=`echo $remote_dir | sed 's,/,_,; s,[~$],,'` 
checksums="checksums-${host}_${remote_dir_name}.sha1"

if [ "$init" = "init" ]; then
	cd Debug
	make dist
	init_remote ${dist_file}.gz
	rm ${dist_file}.gz
	cd ..
else 
	gen_archive $dist_file $checksums
	if [ -f $dist_file ]; then 
		gzip $dist_file
		distribute ${dist_file}.gz
		rm ${dist_file}.gz
	else
		echo "noting to do."
		exit 0
	fi
fi

update_checksums $checksums
#build 

