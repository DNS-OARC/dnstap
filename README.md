# library for DNS encapsulations and transporting of them

[![Bugs](https://sonarcloud.io/api/project_badges/measure?project=dns-oarc%3Adnswire&metric=bugs)](https://sonarcloud.io/summary/new_code?id=dns-oarc%3Adnswire) [![Security Rating](https://sonarcloud.io/api/project_badges/measure?project=dns-oarc%3Adnswire&metric=security_rating)](https://sonarcloud.io/summary/new_code?id=dns-oarc%3Adnswire)

**Currently Work in Progress!**

A C library for encoding/decoding different DNS encapsulations and
transporting them over different protocols.

Supported encapsulations:
- [DNSTAP](http://dnstap.info) using Protobuf

Currently supports:
- Frame Streams using [tinyframe](https://github.com/DNS-OARC/tinyframe)
