%define sover   1
%define libname libdnswire%{sover}
Name:           dnswire
Version:        0.3.1
Release:        1%{?dist}
Summary:        library for DNS encapsulations and transporting of them
Group:          Development/Libraries/C and C++

License:        LGPL-3.0-or-later
URL:            https://github.com/DNS-OARC/dnswire
# Source needs to be generated by dist-tools/create-source-packages, see
# https://github.com/jelu/dist-tools
Source0:        %{name}_%{version}.orig.tar.gz

BuildRequires:  autoconf
BuildRequires:  automake
BuildRequires:  libtool
BuildRequires:  pkgconfig
BuildRequires:  tinyframe-devel
%if 0%{?suse_version} || 0%{?sle_version}
BuildRequires:  protobuf-c
BuildRequires:  libprotobuf-c-devel
%else
BuildRequires:  protobuf-c-compiler
BuildRequires:  protobuf-c-devel
%endif

%description
A C library for encoding/decoding different DNS encapsulations and
transporting them over different protocols.

%package -n %{libname}
Summary:        library for DNS encapsulations and transporting of them
Group:          System/Libraries

%description -n %{libname}
A C library for encoding/decoding different DNS encapsulations and
transporting them over different protocols.

%package devel
Summary:        library for DNS encapsulations and transporting of them - development files
Group:          Development/Libraries/C and C++
Requires:       %{libname} = %{version}
Requires:       tinyframe-devel
%if 0%{?suse_version} || 0%{?sle_version}
Requires:       libprotobuf-c-devel
%else
Requires:       protobuf-c-devel
%endif

%description devel
A C library for encoding/decoding different DNS encapsulations and
transporting them over different protocols.


%prep
%setup -q -n %{name}_%{version}


%build
sh autogen.sh
%configure --disable-examples
make %{?_smp_mflags}


%install
rm -rf $RPM_BUILD_ROOT
make install DESTDIR=$RPM_BUILD_ROOT


%clean
rm -rf $RPM_BUILD_ROOT


%post -n %{libname}
/sbin/ldconfig


%postun -n %{libname}
/sbin/ldconfig


%files -n %{libname}
%defattr(-,root,root,-)
%{_libdir}/libdnswire.so.%{sover}*


%files devel
%defattr(-,root,root,-)
%{_includedir}/*
# %{_mandir}/man3/*
%{_libdir}/libdnswire.so
%{_libdir}/pkgconfig/libdnswire.pc
%exclude %{_libdir}/libdnswire.a
%exclude %{_libdir}/libdnswire.la
%{_datadir}/doc/*


%changelog
* Tue Feb 01 2022 Jerry Lundström <lundstrom.jerry@gmail.com> 0.3.1-1
- Release 0.3.1
  * This is a package only update release to correct mistakes in Debian/
    Ubuntu packages.
  * Bump SO version for Debian/Ubuntu
* Wed Jan 26 2022 Jerry Lundström <lundstrom.jerry@gmail.com> 0.3.0-1
- Release 0.3.0
  * This release updates the Protobuf definition for DNSTAP to include
    new message types, new protocols and the new Policy object.
  * Changes:
    - Update debhelper compatibility level to 10
    - Update to latest `dnstap.pb`, new message types, protocols and message policy
  * Commits:
    87e7909 New dnstap.pb
    f215476 debhelper
    20bf38f Bye Travis
* Fri Oct 23 2020 Jerry Lundström <lundstrom.jerry@gmail.com> 0.2.0-1
- Release 0.2.0
  * This release fixes various issues and bugs in the API, fix typos and
    adds coverage tests.
  * Fixes:
    - `dnstap_decode_protobuf()`: Fix setting of unknown socket family and protocol, was setting DNSTAP_MESSAGE_TYPE_ enums.
    - `enum dnstap_message_type`: Fix typo in unknown enum, now correct `DNSTAP_SOCKET_FAMILY_UNKNOWN`
    - `dnswire_encoder_encode()`: Remove setting state when to the same state it was
    - `dnswire_writer_set_bufsize()`: Fix bug with changing buffer size while having something in the buffer
  * Commits:
    3bfd7e2 Travis, configure
    27f69ab Coverage
    d04b810 Coverage
    ee153d7 Badges
    a381843 Travis
    f3a3e43 COPR
    4b6640f Compile warnings
    bc1b2e2 Funding
    ae537a9 Examples, tests
    c139dd7 LGTM
* Fri Mar 20 2020 Jerry Lundström <lundstrom.jerry@gmail.com> 0.1.1-1
- Release v0.1.1
  * Fix RPM devel package dependencies
  * Commits:
    b451169 package
* Thu Mar 19 2020 Jerry Lundström <lundstrom.jerry@gmail.com> 0.1.0-1
- Release 0.1.0
