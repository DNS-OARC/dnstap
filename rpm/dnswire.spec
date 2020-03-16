%define sover   0
%define libname libdnswire%{sover}
Name:           dnswire
Version:        0.1.0
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
* Mon Mar 16 2020 Jerry Lundström <lundstrom.jerry@gmail.com> 0.1.0-1
- Release 0.1.0
