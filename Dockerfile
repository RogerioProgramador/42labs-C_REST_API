FROM	ubuntu
RUN apt-get update ; \
		apt-get install -y  libmbedtls-dev \
		gcc  \
		make \
		dumb-init \
		libmongoc-1.0-0 \
		libmongoc-dev
WORKDIR	/usr/include
RUN	ln -s libmongoc-1.0/ mongoc; ln -s libbson-1.0/ bson

WORKDIR /infoAPI
COPY	. .
EXPOSE	4242
ENTRYPOINT	["/usr/bin/dumb-init", "make", "run"]
