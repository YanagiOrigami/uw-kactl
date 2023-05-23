bool ExCrt(ll k,ll a,ll p,ll &C,ll &P){
	k%=p,a%=p;
	if(!k&&a) return 0;
	if(!k&&!a) return 1;
	ll x,y,d; d=exgcd(k,p,x,y);
	if(a%d) return 0;
	p/=d,a/=d,k/=d;
	a=mul(a,(x%p+p)%p,p);
	d=exgcd(P,p,x=0,y=0);
	if((a-C)%d) return 0;
	P=P/d*p;
	C=(C+mul(mul(P/p,((a-C)%P+P)%P,P),(x%P+P)%P,P))%P;
	return 1;
}
