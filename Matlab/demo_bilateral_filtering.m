%% Problem: Test mesh denoising using bilateral filtering
%
% Authors : Trung-Thien Tran
% Emal:       trung-thien.tran.1@ulaval.ca; 
%             tranthien9.vn@gmail.com
% Created : 21/06/2014
% From: Fleishman, Shachar, Iddo Drori, and Daniel Cohen-Or. "Bilateral mesh denoising."
% ACM Transactions on Graphics (TOG). Vol. 22. No. 3. ACM, 2003.
% This implementation copyright Trung-Thien Tran 2014, vision.gel.ulaval.ca, 
% but is freely available to copy, use, or modify as long as this line is maintained
clc
clear all
close all

%% Adding all library
% path(path,'U:\THIEN DATA\3-Software');  
% library path (Toolbox_graph Peyre https://www.ceremade.dauphine.fr/~peyre/matlab/graph/content.html

Add_Path(1);

clear options;
name = 'elephant-50kv';
% name = 'fandisk';
% name = 'model_nosphere.ply';

options.name = name; % useful for displaying
[vertex,faces] = read_mesh(name);
if size(vertex,2)>3
    vertex=vertex';
    faces=faces';
end
n=size(vertex,1); % sixe vertices and Normalas are the same


%% Adding noise mesh
vertex=add_noise_mesh(vertex,faces,50);  % noisy data
vertex1=vertex;
figure;
plot_mesh(vertex1, faces);
shading interp;colormap jet
lighting phong


% Now applying Bilateral filtering to the mesh
new_vertex_set=vertex;
it=0;
while (it<1) % number of iteration=2
    vertex=new_vertex_set;
    [normal,~] = compute_normal(vertex,faces);normal=normal';
for i=1:n   % processing each vertex in mesh
    %finding the neighbours
    pi=vertex(i,:);
    ni=normal(i,:);
        
    % subracting from all vertices to see the neighbouring distance
    neighbours=find_vertex_2neighbor(faces,i);
    num_neighbours=size(neighbours,2);
    qi=vertex(neighbours,:);    %% neighbor of pi
    p1=pi;
    pi=mean(qi,1);
    t=sqrt(sum((repmat(pi,num_neighbours,1)-qi).^2,2));sigma_c=2*mean(t);
    h=(sum((repmat(pi,num_neighbours,1)-qi).*repmat(ni,num_neighbours,1),2));
    sigma_s=std(h);
    Wc=exp((-t.^2)./(2*sigma_c^2));
    Ws=exp((-h.^2)./(2*sigma_s^2));
    sum_a=sum(Wc.*Ws.*h);
    normalizer=sum(Wc.*Ws);
    if normalizer==0 | isnan(normalizer)
        new_vertex_set(i,:)=p1;
    else
        new_vertex_set(i,:)=pi-ni*sum_a/normalizer;
    end
end % loop end for vertices
it=it+1;
end

figure;   
plot_mesh(new_vertex_set, faces);
shading interp;
colormap jet
lighting phong

